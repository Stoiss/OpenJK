#include "client.h"
#include "snd_local.h"

#ifdef __USE_BASS__

#include "snd_bass.h"
#include "fast_mutex.h"
#include "tinythread.h"

using namespace tthread;

extern cvar_t		*s_khz;
extern vec3_t		s_entityPosition[MAX_GENTITIES];

extern float S_GetVolumeForChannel ( int entchannel );

qboolean EAX_SUPPORTED = qtrue;

#define MAX_BASS_CHANNELS	256

#define SOUND_3D_METHOD					BASS_3DMODE_NORMAL //BASS_3DMODE_RELATIVE

float MIN_SOUND_RANGE				=	128.0; //256.0
float MAX_SOUND_RANGE				=	2048.0; // 3072.0

int SOUND_CONE_INSIDE_ANGLE			=	120;
int SOUND_CONE_OUTSIDE_ANGLE		=	120;
float SOUND_CONE_OUTSIDE_VOLUME		=	0.9;

// Use meters as distance unit, real world rolloff, real doppler effect
// 1.0 = use meters, 0.9144 = use yards, 0.3048 = use feet.
float SOUND_DISTANCE_UNIT_SIZE		=	0.3048; // UQ1: It would seem that this is close to the right conversion for Q3 units... unsure though...
// 0.0 = no rolloff, 1.0 = real world, 2.0 = 2x real.
float SOUND_REAL_WORLD_FALLOFF		=	1.0; //0.3048
// 0.0 = no doppler, 1.0 = real world, 2.0 = 2x real.
float SOUND_REAL_WORLD_DOPPLER		=	0.3048; //1.0 //0.3048


qboolean BASS_UPDATE_THREAD_RUNNING = qfalse;
qboolean BASS_UPDATE_THREAD_STOP = qfalse;

thread *BASS_UPDATE_THREAD;


// channel (sample/music) info structure
typedef struct {
	DWORD			channel, originalChannel;			// the channel
	BASS_3DVECTOR	pos, vel, ang;	// position,velocity,angles
	vec3_t			origin;
	int				entityNum;
	int				entityChannel;
	float			volume;
	qboolean		isActive;
	qboolean		startRequest;
	qboolean		isLooping;
} Channel;

Channel		MUSIC_CHANNEL;

qboolean	SOUND_CHANNELS_INITIALIZED = qfalse;
Channel		SOUND_CHANNELS[MAX_BASS_CHANNELS];

//
// Channel Utils...
//

void BASS_InitializeChannels ( void )
{
	if (!SOUND_CHANNELS_INITIALIZED)
	{
		for (int c = 0; c < MAX_BASS_CHANNELS; c++) 
		{// Set up this channel...
			memset(&SOUND_CHANNELS[c],0,sizeof(Channel));
		}

		SOUND_CHANNELS_INITIALIZED = qtrue;
	}
}

void BASS_StopChannel ( int chanNum )
{
	if (BASS_ChannelIsActive(SOUND_CHANNELS[chanNum].channel) == BASS_ACTIVE_PLAYING)
	{
		BASS_ChannelStop(SOUND_CHANNELS[chanNum].channel);
		//BASS_ChannelPause(SOUND_CHANNELS[chanNum].channel);
	}

	SOUND_CHANNELS[chanNum].isActive = qfalse;
	SOUND_CHANNELS[chanNum].startRequest = qfalse;
	SOUND_CHANNELS[chanNum].isLooping = qfalse;
}

void BASS_StopEntityChannel ( int entityNum, int entchannel )
{
#pragma omp parallel for num_threads(8)
	for (int c = 0; c < MAX_BASS_CHANNELS; c++) 
	{
		if (SOUND_CHANNELS[c].entityNum == entityNum && SOUND_CHANNELS[c].isActive && SOUND_CHANNELS[c].entityChannel == entchannel)
		{
			BASS_StopChannel(c);
		}
	}
}

void BASS_FindAndStopSound ( DWORD handle )
{
#pragma omp parallel for num_threads(8)
	for (int c = 0; c < MAX_BASS_CHANNELS; c++) 
	{
		if (SOUND_CHANNELS[c].originalChannel == handle && SOUND_CHANNELS[c].isActive)
		{
			BASS_StopChannel(c);
		}
	}
}

void BASS_StopAllChannels ( void )
{
#pragma omp parallel for num_threads(8)
	for (int c = 0; c < MAX_BASS_CHANNELS; c++) 
	{
		if (SOUND_CHANNELS[c].isActive)
		{
			BASS_StopChannel(c);
		}
	}
}

void BASS_StopLoopChannel ( int entityNum )
{
#pragma omp parallel for num_threads(8)
	for (int c = 0; c < MAX_BASS_CHANNELS; c++) 
	{
		if (SOUND_CHANNELS[c].entityNum == entityNum && SOUND_CHANNELS[c].isActive && SOUND_CHANNELS[c].isLooping)
		{
			BASS_StopChannel(c);
		}
	}
}

void BASS_StopAllLoopChannels ( void )
{
#pragma omp parallel for num_threads(8)
	for (int c = 0; c < MAX_BASS_CHANNELS; c++) 
	{
		if (SOUND_CHANNELS[c].isActive && SOUND_CHANNELS[c].isLooping)
		{
			BASS_StopChannel(c);
		}
	}
}

int BASS_FindFreeChannel ( void )
{
	// Fall back to full lookup when we have started too many sounds for the update threade to catch up...
	for (int c = 0; c < MAX_BASS_CHANNELS; c++) 
	{
		if (!SOUND_CHANNELS[c].isActive)
		{
			return c;
		}
	}

	return -1;
}


HINSTANCE			bass = 0;								// bass handle
char				tempfile[MAX_PATH];						// temporary BASS.DLL

void BASS_Shutdown ( void )
{
	if (SOUND_CHANNELS_INITIALIZED)
	{
		BASS_MusicFree(MUSIC_CHANNEL.channel);

		for (int c = 0; c < MAX_BASS_CHANNELS; c++) 
		{// Free channel...
			BASS_StopChannel(c);
			BASS_SampleFree(SOUND_CHANNELS[c].channel);
			BASS_MusicFree(SOUND_CHANNELS[c].channel);
			BASS_StreamFree(SOUND_CHANNELS[c].channel);
		}

		SOUND_CHANNELS_INITIALIZED = qfalse;
	}

	if (thread::hardware_concurrency() > 1)
	{// More then one CPU core. We need to shut down the update thread...
		BASS_UPDATE_THREAD_STOP = qtrue;

		// Wait for update thread to finish...
		BASS_UPDATE_THREAD->join();
		//delete BASS_UPDATE_THREAD;
	}

	BASS_Free();
}

#if 0
/* load BASS and the required functions */
qboolean LoadBASS ( void )
{
	BYTE	*data;
	HANDLE	hfile;
	HRSRC	hres;
	DWORD	len, c;
	char	temppath[MAX_PATH];

	/* get the BASS.DLL resource */

	/*
	if
	(
		!(hres = FindResource( GetModuleHandle( "openjk.x86.exe"), "BASS_DLL", RT_RCDATA)) ||
		!(len = SizeofResource( GetModuleHandle( "openjk.x86.exe"), hres)) ||
		!(hres = (HRSRC)LoadResource( GetModuleHandle( "openjk.x86.exe"), hres)) ||
		!(data = (byte *)LockResource( hres))
	)*/
	if (!(hres=FindResource(GetModuleHandle(NULL),"BASS_DLL",RT_RCDATA))
		|| !(len=SizeofResource(NULL,hres))
		|| !(hres=(HRSRC)LoadResource(NULL,hres))
		|| !(data=(byte *)LockResource(hres)))
	{
		Com_Printf( "Error: Can't get the BASS.DLL resource\n" );
		return ( qfalse );
	}

	/* get a temporary filename */
	GetTempPath( MAX_PATH, temppath );
	GetTempFileName( temppath, "bas", 0, tempfile );

	/* write BASS.DLL to the temporary file */
	if
	(
		INVALID_HANDLE_VALUE ==
			(hfile = CreateFile( tempfile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL))
	)
	{
#ifndef CGAME
		Com_Printf( "Error: Can't write BASS.DLL\n" );
#else
		CG_Printf( "Error: Can't write BASS.DLL\n" );
#endif
		return ( qfalse );
	}

	WriteFile( hfile, data, len, &c, NULL );
	CloseHandle( hfile );

	/* load the temporary BASS.DLL library */
	if ( !(bass = LoadLibrary( tempfile)) )
	{
#ifndef CGAME
		Com_Printf( "Error: Can't load BASS.DLL\n" );
#else
		CG_Printf( "Error: Can't load BASS.DLL\n" );
#endif
		return ( qfalse );
	}

/* "load" all the BASS functions that are to be used */
#define LOADBASSFUNCTION( f )	*( (void **) &f ) = GetProcAddress( bass, #f )
	LOADBASSFUNCTION( BASS_ErrorGetCode );
	LOADBASSFUNCTION( BASS_Init );
	LOADBASSFUNCTION( BASS_Free );
	LOADBASSFUNCTION( BASS_GetCPU );
	LOADBASSFUNCTION( BASS_StreamCreateFile );
	LOADBASSFUNCTION( BASS_StreamCreateURL );
	LOADBASSFUNCTION( BASS_GetDeviceInfo );
	LOADBASSFUNCTION( BASS_Set3DFactors );
	LOADBASSFUNCTION( BASS_Set3DPosition );
	LOADBASSFUNCTION( BASS_SetEAXParameters );
	LOADBASSFUNCTION( BASS_Start );
	LOADBASSFUNCTION( BASS_ChannelSetAttribute );
	LOADBASSFUNCTION( BASS_ChannelSet3DPosition );
	LOADBASSFUNCTION( BASS_ChannelSet3DAttributes );
	LOADBASSFUNCTION( BASS_Apply3D );
	LOADBASSFUNCTION( BASS_ChannelStop );
	LOADBASSFUNCTION( BASS_SampleLoad );
	LOADBASSFUNCTION( BASS_SampleGetChannel );
	LOADBASSFUNCTION( BASS_Set3DPosition );
	LOADBASSFUNCTION( BASS_Set3DPosition );
	LOADBASSFUNCTION( BASS_Set3DPosition );
	LOADBASSFUNCTION( BASS_StreamGetFilePosition );
	LOADBASSFUNCTION( BASS_ChannelPlay );
	LOADBASSFUNCTION( BASS_ChannelBytes2Seconds );
	LOADBASSFUNCTION( BASS_ChannelIsActive );
	LOADBASSFUNCTION( BASS_ChannelIsSliding );
	LOADBASSFUNCTION( BASS_ChannelGetPosition );
	LOADBASSFUNCTION( BASS_ChannelGetLevel );
	LOADBASSFUNCTION( BASS_ChannelSetSync );
	LOADBASSFUNCTION( BASS_GetVersion );
	LOADBASSFUNCTION( BASS_ErrorGetCode );
	LOADBASSFUNCTION( BASS_MusicLoad );
	LOADBASSFUNCTION( BASS_ChannelBytes2Seconds );
	LOADBASSFUNCTION( BASS_ChannelSetSync );
	LOADBASSFUNCTION( BASS_ChannelPlay );
	LOADBASSFUNCTION( BASS_StreamFree );
	LOADBASSFUNCTION( BASS_ChannelIsActive );
	LOADBASSFUNCTION( BASS_ChannelGetLevel );
	LOADBASSFUNCTION( BASS_ChannelGetPosition );
	LOADBASSFUNCTION( BASS_ChannelGetLength );
	LOADBASSFUNCTION( BASS_ChannelGetData );
	LOADBASSFUNCTION( BASS_ChannelGetTags );
	LOADBASSFUNCTION( BASS_SetVolume ); // To set global volume.
	LOADBASSFUNCTION( BASS_ChannelSetAttribute ); // Lets me set chanel volume separetly.

	return ( qtrue );
}
#endif

qboolean BASS_Initialize ( void )
{
#if 0
	if (!LoadBASS()) Com_Error(ERR_FATAL, "Unable to load BASS sound library.\n");
#endif

	EAX_SUPPORTED = qfalse;

	// check the correct BASS was loaded
	if (HIWORD(BASS_GetVersion()) != BASSVERSION) {
		Com_Printf("An incorrect version of BASS.DLL was loaded.");
		return qfalse;
	}

	HWND	win = 0;
	DWORD	freq = 44100;

	if (s_khz->integer == 96)
		freq = 96000;
	else if (s_khz->integer == 48)
		freq = 48000;
	else if (s_khz->integer == 44)
		freq = 44100;
	else if (s_khz->integer == 22)
		freq = 22050;
	else
		freq = 11025;

	Com_Printf("^3BASS Sound System Initializing...\n");

	// Initialize the default output device with 3D support
	if (!BASS_Init(-1, freq, BASS_DEVICE_3D, win, NULL)) {
		Com_Printf("^3- ^5BASS could not find a sound device.");
		Com_Printf("^3BASS Sound System Initialization ^1FAILED^7!\n");
		return qfalse;
	}

	Com_Printf("^5BASS Selected Device:\n");
	BASS_DEVICEINFO info;
	BASS_GetDeviceInfo(BASS_GetDevice(), &info);
	Com_Printf("^3%s^5.\n", info.name);

	// Use meters as distance unit, real world rolloff, real doppler effect
	BASS_Set3DFactors(SOUND_DISTANCE_UNIT_SIZE, SOUND_REAL_WORLD_FALLOFF, SOUND_REAL_WORLD_DOPPLER);

	// Turn EAX off (volume=0), if error then EAX is not supported
	if (!BASS_SetEAXParameters(-1,0,-1,-1))
	{
		Com_Printf("^3+ ^5EAX Features Supported.\n");
		EAX_SUPPORTED = qtrue;
		BASS_SetEAX_NORMAL();
	}
	else
	{
		Com_Printf("^1- ^5EAX Features NOT Supported.\n");
		EAX_SUPPORTED = qfalse;
	}

	BASS_Start();

	BASS_SetConfig(BASS_CONFIG_GVOL_MUSIC, (DWORD)(float)(s_volume->value*10000.0));
	BASS_SetConfig(BASS_CONFIG_GVOL_SAMPLE, (DWORD)(float)(s_volume->value*10000.0));
	BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, (DWORD)(float)(s_volume->value*10000.0));

	BASS_SetConfig(BASS_CONFIG_UPDATETHREADS, (DWORD)16);
	BASS_SetConfig(BASS_CONFIG_BUFFER, (DWORD)100); // set the buffer length

	//Com_Printf("Volume %f. Sample Volume %i. Stream Volume %i.\n", BASS_GetVolume(), (int)BASS_GetConfig(BASS_CONFIG_GVOL_SAMPLE), (int)BASS_GetConfig(BASS_CONFIG_GVOL_STREAM));

	// Initialize all the sound channels ready for use...
	BASS_InitializeChannels();

	// Try to use the WDM full 3D algorythm...
	if (BASS_SetConfig(BASS_CONFIG_3DALGORITHM, BASS_3DALG_FULL))
	{
		Com_Printf("^3+ ^5Enhanced Surround Enabled.\n");
	}
	else
	{
		BASS_SetConfig(BASS_CONFIG_3DALGORITHM, BASS_3DALG_DEFAULT);
		Com_Printf("^1- ^5Default Surround Enabled. You need a WDM sound driver to use Enhanced Surround.\n");
	}

	// Set view angles and position to 0,0,0. We will rotate the sound angles...
	vec3_t forward, right, up;
	BASS_3DVECTOR pos, ang, top, vel;

	vel.x = cl.snap.ps.velocity[0];
	vel.y = cl.snap.ps.velocity[1];
	vel.z = -cl.snap.ps.velocity[2];

	pos.x = cl.snap.ps.origin[0];
	pos.y = cl.snap.ps.origin[1];
	pos.z = cl.snap.ps.origin[2];
	
	AngleVectors(cl.snap.ps.viewangles, forward, right, up);

	ang.x = forward[0];
	ang.y = forward[1];
	ang.z = -forward[2];

	top.x = up[0];
	top.y = up[1];
	top.z = -up[2];

	BASS_Set3DPosition(&pos, &vel, &ang, &top);

	Com_Printf("^3BASS Sound System initialized ^7OK^3!\n");

	BASS_UPDATE_THREAD_STOP = qfalse;

	// UQ1: Play a BASS startup sound...
	//BASS_AddStreamChannel ( "OJK/sound/startup.wav", -1, s_volume->value, NULL );

	return qtrue;
}

//
// Position Utils...
//

void BASS_SetPosition ( int c, vec3_t origin )
{// If the channel's playing then update it's position
	vec3_t soundPos;

	if (!(s_entityPosition[SOUND_CHANNELS[c].entityNum][0] == 0 && s_entityPosition[SOUND_CHANNELS[c].entityNum][1] == 0 && s_entityPosition[SOUND_CHANNELS[c].entityNum][2] == 0))
	{
		VectorCopy(s_entityPosition[SOUND_CHANNELS[c].entityNum], SOUND_CHANNELS[c].origin);
	}
	else if (!(cl.entityBaselines[SOUND_CHANNELS[c].entityNum].origin[0] == 0 && cl.entityBaselines[SOUND_CHANNELS[c].entityNum].origin[1] == 0 && cl.entityBaselines[SOUND_CHANNELS[c].entityNum].origin[2] == 0))
	{
		VectorCopy(cl.entityBaselines[SOUND_CHANNELS[c].entityNum].origin, SOUND_CHANNELS[c].origin);
	}
	else if (origin)
	{
		VectorCopy(origin, SOUND_CHANNELS[c].origin);
	}
	else
	{
		VectorSet(SOUND_CHANNELS[c].origin, 0, 0, 0);
	}

	if (SOUND_CHANNELS[c].entityNum == -1 && SOUND_CHANNELS[c].origin[0] == 0 && SOUND_CHANNELS[c].origin[1] == 0 && SOUND_CHANNELS[c].origin[2] == 0)
	{// Local sound...
		soundPos[0] = cl.snap.ps.origin[0];
		soundPos[1] = cl.snap.ps.origin[1];
		soundPos[2] = cl.snap.ps.origin[2];
	}
	else if (!(SOUND_CHANNELS[c].origin[0] == 0 && SOUND_CHANNELS[c].origin[1] == 0 && SOUND_CHANNELS[c].origin[2] == 0))
	{// We have an origin...
		soundPos[0] = SOUND_CHANNELS[c].origin[0];
		soundPos[1] = SOUND_CHANNELS[c].origin[1];
		soundPos[2] = SOUND_CHANNELS[c].origin[2];
	}
	else
	{
		soundPos[0] = s_entityPosition[SOUND_CHANNELS[c].entityNum][0];
		soundPos[1] = s_entityPosition[SOUND_CHANNELS[c].entityNum][1];
		soundPos[2] = s_entityPosition[SOUND_CHANNELS[c].entityNum][2];
	}

	SOUND_CHANNELS[c].vel.x = 0;//SOUND_CHANNELS[c].pos.x - soundPos[0];
	SOUND_CHANNELS[c].vel.y = 0;//SOUND_CHANNELS[c].pos.y - soundPos[1];
	SOUND_CHANNELS[c].vel.z = 0;//SOUND_CHANNELS[c].pos.z - soundPos[2];

	/*vec3_t vel, forward, right, up;
	vel[0] = SOUND_CHANNELS[c].pos.x - soundPos[0];
	vel[1] = SOUND_CHANNELS[c].pos.x - soundPos[1];
	vel[2] = SOUND_CHANNELS[c].pos.z - soundPos[2];

	AngleVectors(vel, forward, right, up);
	SOUND_CHANNELS[c].vel.x = forward[0];
	SOUND_CHANNELS[c].vel.y = forward[1];
	SOUND_CHANNELS[c].vel.z = -forward[2];*/

	// Set origin...
	SOUND_CHANNELS[c].pos.x = soundPos[0];
	SOUND_CHANNELS[c].pos.y = soundPos[1];
	SOUND_CHANNELS[c].pos.z = soundPos[2];

	BASS_ChannelSetAttribute(SOUND_CHANNELS[c].channel, BASS_ATTRIB_VOL, SOUND_CHANNELS[c].volume*S_GetVolumeForChannel(SOUND_CHANNELS[c].entityChannel));
	BASS_ChannelSet3DPosition(SOUND_CHANNELS[c].channel,&SOUND_CHANNELS[c].pos,NULL,&SOUND_CHANNELS[c].vel);
	BASS_ChannelSet3DAttributes(SOUND_CHANNELS[c].channel, SOUND_3D_METHOD, MIN_SOUND_RANGE, MAX_SOUND_RANGE, SOUND_CONE_INSIDE_ANGLE, SOUND_CONE_OUTSIDE_ANGLE, SOUND_CONE_OUTSIDE_VOLUME);//-1, -1, -1);
	BASS_ChannelFlags(SOUND_CHANNELS[c].channel, BASS_SAMPLE_MUTEMAX, BASS_SAMPLE_MUTEMAX); // enable muting at the max distance
}


void BASS_UpdatePosition ( int c )
{// Update this channel's position, etc...
	vec3_t soundPos;
	// all this gets run every 50ms on every sounds, even ones that dont move - but it is probably required for doppler effect as you run past.
	//if (!SOUND_CHANNELS[c].isLooping) return; // We don't even need to update do we???

	if (!(s_entityPosition[SOUND_CHANNELS[c].entityNum][0] == 0 && s_entityPosition[SOUND_CHANNELS[c].entityNum][1] == 0 && s_entityPosition[SOUND_CHANNELS[c].entityNum][2] == 0))
	{
		VectorCopy(s_entityPosition[SOUND_CHANNELS[c].entityNum], SOUND_CHANNELS[c].origin);
	}
	else if (!(cl.entityBaselines[SOUND_CHANNELS[c].entityNum].origin[0] == 0 && cl.entityBaselines[SOUND_CHANNELS[c].entityNum].origin[1] == 0 && cl.entityBaselines[SOUND_CHANNELS[c].entityNum].origin[2] == 0))
	{
		VectorCopy(cl.entityBaselines[SOUND_CHANNELS[c].entityNum].origin, SOUND_CHANNELS[c].origin);
	}
	else if (!(SOUND_CHANNELS[c].origin[0] == 0 && SOUND_CHANNELS[c].origin[1] == 0 && SOUND_CHANNELS[c].origin[2] == 0))
	{
		
	}
	else
	{
		VectorSet(SOUND_CHANNELS[c].origin, 0, 0, 0);
	}

	if (/*SOUND_CHANNELS[c].entityNum == -1 &&*/ SOUND_CHANNELS[c].origin[0] == 0 && SOUND_CHANNELS[c].origin[1] == 0 && SOUND_CHANNELS[c].origin[2] == 0)
	{// Local sound...
		soundPos[0] = cl.snap.ps.origin[0];
		soundPos[1] = cl.snap.ps.origin[1];
		soundPos[2] = cl.snap.ps.origin[2];
	}
	else if (!(SOUND_CHANNELS[c].origin[0] == 0 && SOUND_CHANNELS[c].origin[1] == 0 && SOUND_CHANNELS[c].origin[2] == 0))
	{// We have an origin...
		soundPos[0] = SOUND_CHANNELS[c].origin[0];
		soundPos[1] = SOUND_CHANNELS[c].origin[1];
		soundPos[2] = SOUND_CHANNELS[c].origin[2];
	}
	else
	{
		soundPos[0] = s_entityPosition[SOUND_CHANNELS[c].entityNum][0];
		soundPos[1] = s_entityPosition[SOUND_CHANNELS[c].entityNum][1];
		soundPos[2] = s_entityPosition[SOUND_CHANNELS[c].entityNum][2];
	}

	//SOUND_CHANNELS[c].vel.x = SOUND_CHANNELS[c].pos.x - soundPos[0];
	//SOUND_CHANNELS[c].vel.y = SOUND_CHANNELS[c].pos.y - soundPos[1];
	//SOUND_CHANNELS[c].vel.z = 0.0-(SOUND_CHANNELS[c].pos.z - soundPos[2]);

	vec3_t vel, forward, right, up;
	vel[0] = SOUND_CHANNELS[c].pos.x - soundPos[0];
	vel[1] = SOUND_CHANNELS[c].pos.x - soundPos[1];
	vel[2] = SOUND_CHANNELS[c].pos.z - soundPos[2];

	AngleVectors(vel, forward, right, up);
	SOUND_CHANNELS[c].vel.x = forward[0];
	SOUND_CHANNELS[c].vel.y = forward[1];
	SOUND_CHANNELS[c].vel.z = -forward[2];

	// Set origin...
	SOUND_CHANNELS[c].pos.x = soundPos[0];
	SOUND_CHANNELS[c].pos.y = soundPos[1];
	SOUND_CHANNELS[c].pos.z = soundPos[2];

	BASS_ChannelSetAttribute(SOUND_CHANNELS[c].channel, BASS_ATTRIB_VOL, SOUND_CHANNELS[c].volume*S_GetVolumeForChannel(SOUND_CHANNELS[c].entityChannel));
	BASS_ChannelSet3DPosition(SOUND_CHANNELS[c].channel,&SOUND_CHANNELS[c].pos,NULL,&SOUND_CHANNELS[c].vel);
	BASS_ChannelSet3DAttributes(SOUND_CHANNELS[c].channel, SOUND_3D_METHOD, MIN_SOUND_RANGE, MAX_SOUND_RANGE, SOUND_CONE_INSIDE_ANGLE, SOUND_CONE_OUTSIDE_ANGLE, SOUND_CONE_OUTSIDE_VOLUME);//-1, -1, -1);
	BASS_ChannelFlags(SOUND_CHANNELS[c].channel, BASS_SAMPLE_MUTEMAX, BASS_SAMPLE_MUTEMAX); // enable muting at the max distance
}

void BASS_ProcessStartRequest( int channel )
{
	Channel *c = &SOUND_CHANNELS[channel];

	c->channel = BASS_SampleGetChannel(c->originalChannel,FALSE); // initialize sample channel

	BASS_ChannelSetAttribute(c->channel, BASS_ATTRIB_VOL, c->volume*S_GetVolumeForChannel(c->entityChannel));
	//BASS_ChannelSlideAttribute( samplechan, BASS_ATTRIB_VOL, c->volume*S_GetVolumeForChannel(entityChannel), 100); // fade-in over 100ms

	// Play
	if (c->isLooping)
		BASS_ChannelPlay(c->channel,TRUE);
	else
		BASS_ChannelPlay(c->channel,FALSE);

	// Apply the 3D changes
	BASS_SetPosition( channel, c->origin );

	SOUND_CHANNELS[channel].startRequest = qfalse;
}

void BASS_UpdateSounds_REAL ( void )
{
	//int NUM_ACTIVE = 0;
	//int NUM_FREE = 0;

	vec3_t forward, right, up;
	BASS_3DVECTOR pos, ang, top, vel;

	vel.x = cl.snap.ps.velocity[0];
	vel.y = cl.snap.ps.velocity[1];
	vel.z = -cl.snap.ps.velocity[2];

	pos.x = cl.snap.ps.origin[0];
	pos.y = cl.snap.ps.origin[1];
	pos.z = cl.snap.ps.origin[2];
	
	AngleVectors(cl.snap.ps.viewangles, forward, right, up);

	ang.x = forward[0];
	ang.y = forward[1];
	ang.z = -forward[2];

	top.x = up[0];
	top.y = up[1];
	top.z = -up[2];

	BASS_Set3DPosition(&pos, &vel, &ang, &top);

	if (s_volumeMusic->value > 0)
	{
		BASS_ChannelSetAttribute(MUSIC_CHANNEL.channel, BASS_ATTRIB_VOL, MUSIC_CHANNEL.volume*S_GetVolumeForChannel(CHAN_MUSIC));
	}

	for (int c = 0; c < MAX_BASS_CHANNELS; c++) 
	{
		if (SOUND_CHANNELS[c].startRequest)
		{// Start any channels that have been requested...
			BASS_ProcessStartRequest( c );
		}
		else if (SOUND_CHANNELS[c].isActive && BASS_ChannelIsActive(SOUND_CHANNELS[c].channel) == BASS_ACTIVE_PLAYING) 
		{// If the channel's playing then update it's position
			BASS_UpdatePosition(c);
		}
		else
		{// Finished. Remove the channel...
			if (SOUND_CHANNELS[c].isActive)
			{// Still marked as active. Stop the channel and reset it...
				//Com_Printf("Removing inactive channel %i.\n", c);
				BASS_StopChannel(c);
				memset(&SOUND_CHANNELS[c],0,sizeof(Channel));
			}
		}

		//if (SOUND_CHANNELS[c].isActive)
		//	NUM_ACTIVE++;
		//else
		//	NUM_FREE++;
	}

	// Apply the 3D changes.
	BASS_Apply3D();

	//Com_Printf("There are currently %i active and %i free channels. Free ch list size %i.\n", NUM_ACTIVE, NUM_FREE, current_free_channel);
}

void BASS_UpdateThread(void * aArg)
{
	while (!BASS_UPDATE_THREAD_STOP)
	{
		BASS_UpdateSounds_REAL();
		this_thread::sleep_for(chrono::milliseconds(50));
	}

	BASS_UPDATE_THREAD_RUNNING = qfalse;
}

void BASS_UpdateSounds ( void )
{
	if (thread::hardware_concurrency() <= 1)
	{// Only one CPU core to use. Don't thread...
		BASS_UpdateSounds_REAL();
		return;
	}

	if (!BASS_UPDATE_THREAD_RUNNING)
	{
		BASS_UPDATE_THREAD_RUNNING = qtrue;
		BASS_UPDATE_THREAD = new thread (BASS_UpdateThread, 0);
	}
}

//
// Effects...
//

/*
// EAX presets, usage: BASS_SetEAXParameters(EAX_PRESET_xxx)
#define EAX_PRESET_GENERIC         EAX_ENVIRONMENT_GENERIC,0.5F,1.493F,0.5F
#define EAX_PRESET_PADDEDCELL      EAX_ENVIRONMENT_PADDEDCELL,0.25F,0.1F,0.0F
#define EAX_PRESET_ROOM            EAX_ENVIRONMENT_ROOM,0.417F,0.4F,0.666F
#define EAX_PRESET_BATHROOM        EAX_ENVIRONMENT_BATHROOM,0.653F,1.499F,0.166F
#define EAX_PRESET_LIVINGROOM      EAX_ENVIRONMENT_LIVINGROOM,0.208F,0.478F,0.0F
#define EAX_PRESET_STONEROOM       EAX_ENVIRONMENT_STONEROOM,0.5F,2.309F,0.888F
#define EAX_PRESET_AUDITORIUM      EAX_ENVIRONMENT_AUDITORIUM,0.403F,4.279F,0.5F
#define EAX_PRESET_CONCERTHALL     EAX_ENVIRONMENT_CONCERTHALL,0.5F,3.961F,0.5F
#define EAX_PRESET_CAVE            EAX_ENVIRONMENT_CAVE,0.5F,2.886F,1.304F
#define EAX_PRESET_ARENA           EAX_ENVIRONMENT_ARENA,0.361F,7.284F,0.332F
#define EAX_PRESET_HANGAR          EAX_ENVIRONMENT_HANGAR,0.5F,10.0F,0.3F
#define EAX_PRESET_CARPETEDHALLWAY EAX_ENVIRONMENT_CARPETEDHALLWAY,0.153F,0.259F,2.0F
#define EAX_PRESET_HALLWAY         EAX_ENVIRONMENT_HALLWAY,0.361F,1.493F,0.0F
#define EAX_PRESET_STONECORRIDOR   EAX_ENVIRONMENT_STONECORRIDOR,0.444F,2.697F,0.638F
#define EAX_PRESET_ALLEY           EAX_ENVIRONMENT_ALLEY,0.25F,1.752F,0.776F
#define EAX_PRESET_FOREST          EAX_ENVIRONMENT_FOREST,0.111F,3.145F,0.472F
#define EAX_PRESET_CITY            EAX_ENVIRONMENT_CITY,0.111F,2.767F,0.224F
#define EAX_PRESET_MOUNTAINS       EAX_ENVIRONMENT_MOUNTAINS,0.194F,7.841F,0.472F
#define EAX_PRESET_QUARRY          EAX_ENVIRONMENT_QUARRY,1.0F,1.499F,0.5F
#define EAX_PRESET_PLAIN           EAX_ENVIRONMENT_PLAIN,0.097F,2.767F,0.224F
#define EAX_PRESET_PARKINGLOT      EAX_ENVIRONMENT_PARKINGLOT,0.208F,1.652F,1.5F
#define EAX_PRESET_SEWERPIPE       EAX_ENVIRONMENT_SEWERPIPE,0.652F,2.886F,0.25F
#define EAX_PRESET_UNDERWATER      EAX_ENVIRONMENT_UNDERWATER,1.0F,1.499F,0.0F
#define EAX_PRESET_DRUGGED         EAX_ENVIRONMENT_DRUGGED,0.875F,8.392F,1.388F
#define EAX_PRESET_DIZZY           EAX_ENVIRONMENT_DIZZY,0.139F,17.234F,0.666F
#define EAX_PRESET_PSYCHOTIC       EAX_ENVIRONMENT_PSYCHOTIC,0.486F,7.563F,0.806F
	*/

void BASS_SetEAX_NORMAL ( void )
{
	if (!EAX_SUPPORTED) return;

	BASS_SetEAXParameters(EAX_PRESET_GENERIC);
}

void BASS_SetEAX_UNDERWATER ( void )
{
	if (!EAX_SUPPORTED) return;

	BASS_SetEAXParameters(EAX_PRESET_UNDERWATER);
}

void BASS_SetRolloffFactor ( int factor )
{
	BASS_Set3DFactors(-1,pow(2,(factor-10)/5.0),-1);
}

void BASS_SetDopplerFactor ( int factor )
{
	BASS_Set3DFactors(-1,-1,pow(2,(factor-10)/5.0));
}

//
// Music Tracks...
//

void BASS_StopMusic( void )
{
	// Free old samples...
	if (BASS_ChannelIsActive(MUSIC_CHANNEL.channel) == BASS_ACTIVE_PLAYING)
	{
		BASS_ChannelStop(MUSIC_CHANNEL.channel);
	}
}

void BASS_StartMusic ( DWORD samplechan )
{
	if (s_volumeMusic->value <= 0) return;

	BASS_StopMusic();

	// Set new samples...
	MUSIC_CHANNEL.originalChannel=MUSIC_CHANNEL.channel = samplechan;
	MUSIC_CHANNEL.entityNum = -1;
	MUSIC_CHANNEL.entityChannel = CHAN_MUSIC;
	MUSIC_CHANNEL.volume = 1.0;

	BASS_SampleGetChannel(samplechan,FALSE); // initialize sample channel
	BASS_ChannelSetAttribute(samplechan, BASS_ATTRIB_VOL, MUSIC_CHANNEL.volume*S_GetVolumeForChannel(CHAN_MUSIC));

	// Play
	BASS_ChannelPlay(samplechan,TRUE);

	// Apply the 3D settings (music is always local)...
	MUSIC_CHANNEL.vel.x = 0;
	MUSIC_CHANNEL.vel.y = 0;
	MUSIC_CHANNEL.vel.z = 0;

	// Set origin...
	MUSIC_CHANNEL.pos.x = 0;
	MUSIC_CHANNEL.pos.y = 0;
	MUSIC_CHANNEL.pos.z = 0;

	BASS_ChannelSet3DPosition(MUSIC_CHANNEL.channel, &MUSIC_CHANNEL.pos, NULL, &MUSIC_CHANNEL.vel);
	BASS_ChannelSet3DAttributes(MUSIC_CHANNEL.channel, SOUND_3D_METHOD, -1, -1, -1, -1, -1);
	BASS_Apply3D();
}

DWORD BASS_LoadMusicSample ( void *memory, int length )
{// Just load a sample into memory ready to play instantly...
	DWORD newchan;

	if (s_volumeMusic->value <= 0) return -1;

	// Try to load the sample with the highest quality options we support...
	if (newchan=BASS_SampleLoad(TRUE,memory,0,(DWORD)length,1,BASS_SAMPLE_LOOP|BASS_SAMPLE_FLOAT))
	{
		return newchan;
	}
	else if (newchan=BASS_SampleLoad(TRUE,memory,0,(DWORD)length,1,BASS_SAMPLE_SOFTWARE|BASS_SAMPLE_LOOP|BASS_SAMPLE_FLOAT))
	{
		return newchan;
	}
	else if (newchan=BASS_SampleLoad(TRUE,memory,0,(DWORD)length,1,BASS_SAMPLE_LOOP))
	{
		return newchan;
	}
	else if (newchan=BASS_SampleLoad(TRUE,memory,0,(DWORD)length,1,BASS_SAMPLE_SOFTWARE|BASS_SAMPLE_LOOP))
	{
		return newchan;
	}

	return -1;
}


//
// Sounds...
//

void BASS_AddStreamChannel ( char *file, int entityNum, int entityChannel, vec3_t origin )
{
#if 0
	DWORD newchan;
	int chan = BASS_FindFreeChannel();

	if (chan < 0)
	{// No channel left to play on...
		Com_Printf("BASS: No free sound channels.\n");
		return;
	}

	// Load a music or sample from "file"
	if (newchan=BASS_SampleLoad(FALSE,file,0,0,1,BASS_SAMPLE_3D|BASS_SAMPLE_MONO)) {
			Channel *c = SOUND_CHANNELS[chan];
			memset(c,0,sizeof(Channel));
			c->originalChannel=c->channel=newchan;
			c->entityNum = entityNum;
			c->entityChannel = entityChannel;
			c->isActive = qtrue;
			c->isLooping = qfalse;
			c->volume = 1.0;

			BASS_SampleGetChannel(newchan,FALSE); // initialize sample channel
			BASS_ChannelSetAttribute(newchan, BASS_ATTRIB_VOL, c->volume*S_GetVolumeForChannel(entityChannel));

			// Play
			BASS_ChannelPlay(newchan,FALSE);

			// Apply the 3D changes
			BASS_SetPosition( chan, origin );
			BASS_ChannelSet3DAttributes(newchan, SOUND_3D_METHOD, 256.0, -1, -1, -1, -1);//120, 120, 0.5);
			BASS_Apply3D();
	} else {
		Com_Printf("Can't load file (note samples must be mono)\n");
	}
#endif
}

void BASS_AddMemoryChannel ( DWORD samplechan, int entityNum, int entityChannel, vec3_t origin, float volume )
{
	int chan = BASS_FindFreeChannel();

	if (chan < 0)
	{// No channel left to play on...
		Com_Printf("BASS: No free sound channels.\n");
		return;
	}

	// Load a music or sample from "file" (memory)
	Channel *c = &SOUND_CHANNELS[chan];
	c->originalChannel=c->channel=samplechan;
	c->entityNum = entityNum;
	c->entityChannel = entityChannel;
	c->volume = volume;

	if (origin) VectorCopy(origin, c->origin);
	else VectorSet(c->origin, 0, 0, 0);

	c->isActive = qtrue;
	c->isLooping = qfalse;
	c->startRequest = qtrue;
}

void BASS_AddMemoryLoopChannel ( DWORD samplechan, int entityNum, int entityChannel, vec3_t origin, float volume )
{
	int chan = BASS_FindFreeChannel();

	if (chan < 0)
	{// No channel left to play on...
		Com_Printf("BASS: No free sound channels.\n");
		return;
	}

	//
	// UQ1: Since it seems these also re-call this function to update positions, etc, run a check first...
	//
	if (origin)
	{// If there's no origin, surely this can't be an update...
		for (int ch = 0; ch < MAX_BASS_CHANNELS; ch++) 
		{
			if (SOUND_CHANNELS[ch].isActive && SOUND_CHANNELS[ch].isLooping)
			{// This is active and looping...
				if (SOUND_CHANNELS[ch].entityChannel == entityChannel 
					&& SOUND_CHANNELS[ch].entityNum == entityNum 
					&& SOUND_CHANNELS[ch].originalChannel == samplechan)
				{// This is our sound! Just update it (and then return)...
					Channel *c = &SOUND_CHANNELS[ch];
					VectorCopy(origin, c->origin);
					c->volume = volume;
					//Com_Printf("BASS DEBUG: Sound position (%f %f %f) and volume (%f) updated.\n", origin[0], origin[1], origin[2], volume);
					return;
				}
			}
		}
	}

	// Load a music or sample from "file" (memory)
	Channel *c = &SOUND_CHANNELS[chan];
	c->originalChannel=c->channel=samplechan;
	c->entityNum = entityNum;
	c->entityChannel = entityChannel;
	c->volume = volume;

	if (origin) VectorCopy(origin, c->origin);
	else VectorSet(c->origin, 0, 0, 0);

	c->isActive = qtrue;
	c->isLooping = qtrue;
	c->startRequest = qtrue;
}

DWORD BASS_LoadMemorySample ( void *memory, int length )
{// Just load a sample into memory ready to play instantly...
	DWORD newchan;

	// Try to load the sample with the highest quality options we support...
	if ((newchan=BASS_SampleLoad(TRUE,memory,0,(DWORD)length,16,BASS_SAMPLE_3D|BASS_SAMPLE_MONO|BASS_SAMPLE_FLOAT)))
	{
		return newchan;
	}
	else if ((newchan=BASS_SampleLoad(TRUE,memory,0,(DWORD)length,16,BASS_SAMPLE_3D|BASS_SAMPLE_SOFTWARE|BASS_SAMPLE_MONO|BASS_SAMPLE_FLOAT)))
	{
		return newchan;
	}
	else if ((newchan=BASS_SampleLoad(TRUE,memory,0,(DWORD)length,16,BASS_SAMPLE_3D|BASS_SAMPLE_MONO)))
	{
		return newchan;
	}
	else if ((newchan=BASS_SampleLoad(TRUE,memory,0,(DWORD)length,16,BASS_SAMPLE_3D|BASS_SAMPLE_SOFTWARE|BASS_SAMPLE_MONO)))
	{
		return newchan;
	}

	return -1;
}

#endif //__USE_BASS__

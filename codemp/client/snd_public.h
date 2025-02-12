#pragma once

#include "qcommon/qcommon.h"
#include "snd_local.h"

extern void S_TextToSpeech( const char *text, const char *voice, int entityNum, float *origin );
extern qboolean S_DownloadVoice( const char *text, const char *voice );
extern void ShutdownTextToSpeechThread ( void );

void S_Init( void );
void S_Shutdown( void );

// if origin is NULL, the sound will be dynamically sourced from the entity
void S_AddAmbientLoopingSound( const vec3_t origin, unsigned char volume, sfxHandle_t sfxHandle );
void S_StartAmbientSound( const vec3_t origin, int entityNum, unsigned char volume, sfxHandle_t sfxHandle );
void S_MuteSound(int entityNum, int entchannel);
void S_StartSound( const vec3_t origin, int entnum, int entchannel, sfxHandle_t sfx );
void S_StartLocalSound( sfxHandle_t sfx, int channelNum );
void S_StartLocalLoopingSound( sfxHandle_t sfx);

void S_RestartMusic( void );
void S_StartBackgroundTrack( const char *intro, const char *loop, qboolean bCalledByCGameStart );
void S_StopBackgroundTrack( void );

// stop all sounds
void S_StopSounds(void);	// from snd_dma.cpp
// stop all sounds and the background track
void S_StopAllSounds( void );

// all continuous looping sounds must be added before calling S_Update
void S_ClearLoopingSounds( void );
void S_StopLoopingSound( int entityNum );
void S_AddLoopingSound( int entityNum, const vec3_t origin, const vec3_t velocity, sfxHandle_t sfx );

// recompute the reletive volumes for all running sounds
// relative to the given entityNum / orientation
void S_Respatialize( int entityNum, const vec3_t head, matrix3_t axis, int inwater );

// let the sound system know where an entity currently is
void S_UpdateEntityPosition( int entityNum, const vec3_t origin );

void S_Update( void );

void S_DisableSounds( void );

void S_BeginRegistration( void );

// RegisterSound will allways return a valid sample, even if it
// has to create a placeholder.  This prevents continuous filesystem
// checks for missing files
sfxHandle_t	S_RegisterSound( const char *sample );

extern qboolean s_shutUp;

void S_FreeAllSFXMem(void);


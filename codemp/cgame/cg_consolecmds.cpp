// Copyright (C) 1999-2000 Id Software, Inc.
//
// cg_consolecmds.c -- text commands typed in at the local console, or
// executed by a key binding

#include "cg_local.h"
#include "game/bg_saga.h"
//#include "game/bg_class.h"

/*
=================
CG_TargetCommand_f

=================
*/
void CG_TargetCommand_f( void ) {
	int		targetNum;
	char	test[4];

	targetNum = CG_CrosshairPlayer();
	if ( targetNum == -1 ) {
		return;
	}

	trap->Cmd_Argv( 1, test, 4 );
	trap->SendClientCommand( va( "gc %i %i", targetNum, atoi( test ) ) );
}

/*
=================
CG_SizeUp_f

Keybinding command
=================
*/
static void CG_SizeUp_f (void) {
	trap->Cvar_Set( "cg_viewsize", va( "%i", cg_viewsize.integer + 10 ) );
}

/*
=================
CG_SizeDown_f

Keybinding command
=================
*/
static void CG_SizeDown_f (void) {
	trap->Cvar_Set( "cg_viewsize", va( "%i", cg_viewsize.integer - 10 ) );
}

/*
=============
CG_Viewpos_f

Debugging command to print the current position
=============
*/
static void CG_Viewpos_f (void) {
	trap->Print ("%s (%i %i %i) : %i\n", cgs.mapname, (int)cg.refdef.vieworg[0],
		(int)cg.refdef.vieworg[1], (int)cg.refdef.vieworg[2],
		(int)cg.refdef.viewangles[YAW]);
}

/*
=================
CG_ScoresDown_f

=================
*/
static void CG_ScoresDown_f( void ) {

	CG_BuildSpectatorString();
	if ( cg.scoresRequestTime + 2000 < cg.time ) {
		// the scores are more than two seconds out of data,
		// so request new ones
		cg.scoresRequestTime = cg.time;
		trap->SendClientCommand( "score" );

		// leave the current scores up if they were already
		// displayed, but if this is the first hit, clear them out
		if ( !cg.showScores ) {
			cg.showScores = qtrue;
			cg.numScores = 0;
		}
	} else {
		// show the cached contents even if they just pressed if it
		// is within two seconds
		cg.showScores = qtrue;
	}
}

/*
=================
CG_ScoresUp_f

=================
*/
static void CG_ScoresUp_f( void ) {
	if ( cg.showScores ) {
		cg.showScores = qfalse;
		cg.scoreFadeTime = cg.time;
	}
}

void CG_ClientList_f( void )
{
	clientInfo_t *ci;
	int i;
	int count = 0;

	for( i = 0; i < MAX_CLIENTS; i++ )
	{
		ci = &cgs.clientinfo[ i ];
		if( !ci->infoValid )
			continue;

		switch( ci->team )
		{
		case FACTION_FREE:
			Com_Printf( "%2d " S_COLOR_YELLOW "F   " S_COLOR_WHITE "%s" S_COLOR_WHITE "%s\n", i, ci->name, (ci->botSkill != -1) ? " (bot)" : "" );
			break;

		case FACTION_EMPIRE:
			Com_Printf( "%2d " S_COLOR_RED "R   " S_COLOR_WHITE "%s" S_COLOR_WHITE "%s\n", i,
				ci->name, (ci->botSkill != -1) ? " (bot)" : "" );
			break;

		case FACTION_REBEL:
			Com_Printf( "%2d " S_COLOR_BLUE "B   " S_COLOR_WHITE "%s" S_COLOR_WHITE "%s\n", i,
				ci->name, (ci->botSkill != -1) ? " (bot)" : "" );
			break;

		case FACTION_MANDALORIAN:
			Com_Printf( "%2d " S_COLOR_ORANGE "B   " S_COLOR_WHITE "%s" S_COLOR_WHITE "%s\n", i,
				ci->name, (ci->botSkill != -1) ? " (bot)" : "" );
			break;

		case FACTION_MERC:
			Com_Printf( "%2d " S_COLOR_GREEN "B   " S_COLOR_WHITE "%s" S_COLOR_WHITE "%s\n", i,
				ci->name, (ci->botSkill != -1) ? " (bot)" : "" );
			break;

		case FACTION_WILDLIFE:
			Com_Printf("%2d " S_COLOR_YELLOW "B   " S_COLOR_WHITE "%s" S_COLOR_WHITE "%s\n", i,
				ci->name, (ci->botSkill != -1) ? " (bot)" : "");
			break;

		default:
		case FACTION_SPECTATOR:
			Com_Printf( "%2d " S_COLOR_YELLOW "S   " S_COLOR_WHITE "%s" S_COLOR_WHITE "%s\n", i, ci->name, (ci->botSkill != -1) ? " (bot)" : "" );
			break;
		}

		count++;
	}

	Com_Printf( "Listed %2d clients\n", count );
}


static void CG_TellTarget_f( void ) {
	int		clientNum;
	char	command[128];
	char	message[128];

	clientNum = CG_CrosshairPlayer();
	if ( clientNum == -1 ) {
		return;
	}

	trap->Cmd_Args( message, 128 );
	Com_sprintf( command, 128, "tell %i %s", clientNum, message );
	trap->SendClientCommand( command );
}

static void CG_TellAttacker_f( void ) {
	int		clientNum;
	char	command[128];
	char	message[128];

	clientNum = CG_LastAttacker();
	if ( clientNum == -1 ) {
		return;
	}

	trap->Cmd_Args( message, 128 );
	Com_sprintf( command, 128, "tell %i %s", clientNum, message );
	trap->SendClientCommand( command );
}

/*
==================
CG_StartOrbit_f
==================
*/

static void CG_StartOrbit_f( void ) {
	char var[MAX_TOKEN_CHARS];

	trap->Cvar_VariableStringBuffer( "developer", var, sizeof( var ) );
	if ( !atoi(var) ) {
		return;
	}
	if (cg_cameraOrbit.value != 0) {
		trap->Cvar_Set ("cg_cameraOrbit", "0");
		trap->Cvar_Set("cg_thirdPerson", "0");
	} else {
		trap->Cvar_Set("cg_cameraOrbit", "5");
		trap->Cvar_Set("cg_thirdPerson", "1");
		trap->Cvar_Set("cg_thirdPersonAngle", "0");
		trap->Cvar_Set("cg_thirdPersonRange", "160");
	}
}

void CG_SiegeBriefingDisplay(int team, int dontshow);
static void CG_SiegeBriefing_f(void)
{
	int team;

	if (cgs.gametype != GT_SIEGE)
	{ //Cannot be displayed unless in this gametype
		return;
	}

	team = cg.predictedPlayerState.persistant[PERS_TEAM];

	if (team != SIEGETEAM_TEAM1 &&
		team != SIEGETEAM_TEAM2)
	{ //cannot be displayed if not on a valid team
		return;
	}

	CG_SiegeBriefingDisplay(team, 0);
}

static void CG_SiegeCvarUpdate_f(void)
{
	int team;

	if (cgs.gametype != GT_SIEGE)
	{ //Cannot be displayed unless in this gametype
		return;
	}

	team = cg.predictedPlayerState.persistant[PERS_TEAM];

	if (team != SIEGETEAM_TEAM1 &&
		team != SIEGETEAM_TEAM2)
	{ //cannot be displayed if not on a valid team
		return;
	}

	CG_SiegeBriefingDisplay(team, 1);
}

static void CG_SiegeCompleteCvarUpdate_f(void)
{
	if (cgs.gametype != GT_SIEGE)
	{ //Cannot be displayed unless in this gametype
		return;
	}

	// Set up cvars for both teams
	CG_SiegeBriefingDisplay(SIEGETEAM_TEAM1, 1);
	CG_SiegeBriefingDisplay(SIEGETEAM_TEAM2, 1);
}

extern void FOLIAGE_GenerateFoliage ( void );

//[AUTOWAYPOINT]
extern void AIMod_AutoWaypoint ( void );
extern void AIMod_AutoWaypoint_Clean ( void );
extern void AIMod_MarkBadHeight ( void );
extern void AIMod_AddRemovalPoint ( void );
extern void AIMod_AddLiftPoint ( void );
extern void AIMod_AWC_MarkBadHeight ( void );
extern void AIMod_AddWayPoint ( void );
extern void CG_ShowSurface ( void );
extern void CG_ShowForwardSurface ( void );
extern void CG_ShowSkySurface ( void );
extern void CG_ShowSlope ( void );

void CG_ShowLifts ( void )
{
	int i = 0;
	int count = 0;

	for (i = 0; i < MAX_GENTITIES; i++)
	{
		centity_t *cent = &cg_entities[i];

		if (!cent) continue;
		if (cent->currentState.eType != ET_MOVER_MARKER) continue;
		
		count++;
		trap->Print("Mover found at %f %f %f (top %f %f %f).\n", cent->currentState.origin[0], cent->currentState.origin[1], cent->currentState.origin[2]
		, cent->currentState.origin2[0], cent->currentState.origin2[1], cent->currentState.origin2[2]);
	}

	trap->Print("There are %i movers.\n", count);
}
//[/AUTOWAYPOINT]

void	Clcmd_EntityList_f (void) {
	int			e;
	centity_t		*check;

	check = cg_entities;
	for (e = 0; e < MAX_GENTITIES ; e++, check++) {
		if ( !check || check->currentState.eType == ET_FREED ) {
			continue;
		}
		if ( check->currentState.origin[0] == 0 && check->currentState.origin[1] == 0 && check->currentState.origin[2] == 0) {
			continue;
		}
		trap->Print("%3i:", e);
		switch ( check->currentState.eType ) {
		case ET_GENERAL:
			trap->Print("ET_GENERAL          ");
			break;
		case ET_PLAYER:
			trap->Print("ET_PLAYER           ");
			break;
		case ET_ITEM:
			trap->Print("ET_ITEM             ");
			break;
		case ET_MISSILE:
			trap->Print("ET_MISSILE          ");
			break;
		case ET_SPECIAL:
			trap->Print("ET_SPECIAL          ");
			break;
		case ET_HOLOCRON:
			trap->Print("ET_HOLOCRON         ");
			break;
		case ET_MOVER:
			trap->Print("ET_MOVER            ");
			break;
		case ET_BEAM:
			trap->Print("ET_BEAM             ");
			break;
		case ET_PORTAL:
			trap->Print("ET_PORTAL           ");
			break;
		case ET_SPEAKER:
			trap->Print("ET_SPEAKER          ");
			break;
		case ET_PUSH_TRIGGER:
			trap->Print("ET_PUSH_TRIGGER     ");
			break;
		case ET_TELEPORT_TRIGGER:
			trap->Print("ET_TELEPORT_TRIGGER ");
			break;
		case ET_INVISIBLE:
			trap->Print("ET_INVISIBLE        ");
			break;
		case ET_NPC:
			trap->Print("ET_NPC              ");
			break;
		case ET_TEAM:
			trap->Print("ET_TEAM             ");
			break;
		case ET_BODY:
			trap->Print("ET_BODY             ");
			break;
		case ET_TERRAIN:
			trap->Print("ET_TERRAIN          ");
			break;
		case ET_FX:
			trap->Print("ET_FX               ");
			break;
		case ET_MOVER_MARKER:
			trap->Print("ET_MOVER_MARKER     ");
			break;
		case ET_SPAWNPOINT:
			trap->Print("ET_SPAWNPOINT       ");
			break;
		case ET_FREED:
			trap->Print("ET_FREED            ");
			break;
		case ET_TRIGGER_HURT:
			trap->Print("ET_TRIGGER_HURT     ");
			break;
		default:
			trap->Print("%-3i                ", check->currentState.eType);
			break;
		}

		trap->Print(" - origin %f %f %f.", check->currentState.origin[0], check->currentState.origin[1], check->currentState.origin[2]);
		trap->Print("\n");
	}
}

typedef struct consoleCommand_s {
	const char	*cmd;
	void		(*func)(void);
} consoleCommand_t;

int cmdcmp( const void *a, const void *b ) {
	return Q_stricmp( (const char *)a, ((consoleCommand_t*)b)->cmd );
}

#ifdef __USE_NAVMESH__
extern void Warzone_Nav_CreateNavMesh(void);
#endif //__USE_NAVMESH__
extern void AWP_AutoWaypoint2(void);

extern void CG_AddCubeMap(void);
extern void CG_DisableCubeMap(void);
extern void CG_EnableCubeMap(void);

/* This array MUST be sorted correctly by alphabetical name field */ // UQ1: And who thought this change was a good idea??? *grrr*
static consoleCommand_t	commands[] = {
	{ "+scores",					CG_ScoresDown_f },
	{ "-scores",					CG_ScoresUp_f },
	{ "adw",						AIMod_AddWayPoint },
	{ "autowaypoint",				AIMod_AutoWaypoint },
	{ "autowaypointclean",			AIMod_AutoWaypoint_Clean },
	{ "awc",						AIMod_AutoWaypoint_Clean },
	{ "awc_addbadheight",			AIMod_AWC_MarkBadHeight },
	{ "awc_addlift",				AIMod_AddLiftPoint },
	{ "awc_addremovalspot",			AIMod_AddRemovalPoint },
	{ "awc_addwaypoint",			AIMod_AddWayPoint },
	{ "awp",						AIMod_AutoWaypoint },
	{ "awp2",						AWP_AutoWaypoint2 },
	{ "awp_badheight",				AIMod_MarkBadHeight },
	{ "briefing",					CG_SiegeBriefing_f },
	{ "cg_entitylist",				Clcmd_EntityList_f },
	{ "clientlist",					CG_ClientList_f },
	{ "cubemap_add",				CG_AddCubeMap },
	{ "cubemap_disable",			CG_DisableCubeMap },
	{ "cubemap_enable",				CG_EnableCubeMap },
	{ "forcenext",					CG_NextForcePower_f },
	{ "forceprev",					CG_PrevForcePower_f },
	{ "generatefoliagepositions",	FOLIAGE_GenerateFoliage },
	{ "genfoliage",					FOLIAGE_GenerateFoliage },
	{ "invnext",					CG_NextInventory_f },
	{ "invprev",					CG_PrevInventory_f },
	{ "loaddeferred",				CG_LoadDeferredPlayers },
#ifdef __USE_NAVMESH__
	{ "navgen",						Warzone_Nav_CreateNavMesh },
#endif //__USE_NAVMESH__
	{ "nextframe",					CG_TestModelNextFrame_f },
	{ "nextskin",					CG_TestModelNextSkin_f },
	{ "prevframe",					CG_TestModelPrevFrame_f },
	{ "prevskin",					CG_TestModelPrevSkin_f },
	{ "showforwardsurface",			CG_ShowForwardSurface },
	{ "showlifts",					CG_ShowLifts },
	{ "showskysurface",				CG_ShowSkySurface },
	{ "showslope",					CG_ShowSlope },
	{ "showsurface",				CG_ShowSurface },
	{ "siegeCompleteCvarUpdate",	CG_SiegeCompleteCvarUpdate_f },
	{ "siegeCvarUpdate",			CG_SiegeCvarUpdate_f },
	{ "sizedown",					CG_SizeDown_f },
	{ "sizeup",						CG_SizeUp_f },
	{ "startOrbit",					CG_StartOrbit_f },
	{ "tcmd",						CG_TargetCommand_f },
	{ "tell_attacker",				CG_TellAttacker_f },
	{ "tell_target",				CG_TellTarget_f },
	{ "testgun",					CG_TestGun_f },
	{ "testmodel",					CG_TestModel_f },
	{ "tts",						TTS_SayText },
	{ "ttsprecache",				CG_DownloadAllTextToSpeechSounds },
	{ "viewpos",					CG_Viewpos_f },
	{ "weapnext",					CG_NextWeapon_f },
	{ "weapon",						CG_Weapon_f },
	{ "weaponclean",				CG_WeaponClean_f },
	{ "weapprev",					CG_PrevWeapon_f },
	{ "zzz",						CG_SaySillyTextTest },
	{ "zoomin",						CG_ZoomIn_f	},
	{ "zoomout",					CG_ZoomOut_f },
};

static const size_t numCommands = ARRAY_LEN( commands );

/*
=================
CG_ConsoleCommand

The string has been tokenized and can be retrieved with
Cmd_Argc() / Cmd_Argv()
=================
*/
qboolean CG_ConsoleCommand( void ) {
	consoleCommand_t	*command = NULL;

	command = (consoleCommand_t *)bsearch( CG_Argv( 0 ), commands, numCommands, sizeof( commands[0] ), cmdcmp );

	if ( !command )
		return qfalse;

	command->func();
	return qtrue;
}

static const char *gcmds[] = {
	"addbot",
	"callteamvote",
	"callvote",
	"duelteam",
	"follow",
	"follownext",
	"followprev",
	"forcechanged",
	"give",
	"god",
	"kill",
	"levelshot",
	"loaddefered",
	"noclip",
	"notarget",
	"NPC",
	"say",
	"say_team",
	"setviewpos",
	"siegeclass",
	"stats",
	//"stopfollow",
//	"tb",
	"team",
	"teamtask",
	"teamvote",
	"tell",
	"vehicle",
	"voice_cmd",
	"vote",
	"where",
	"zoom"
};
static const size_t numgcmds = ARRAY_LEN( gcmds );

/*
=================
CG_InitConsoleCommands

Let the client system know about all of our commands
so it can perform tab completion
=================
*/
void CG_InitConsoleCommands( void ) {
	size_t i;

	for ( i = 0 ; i < numCommands ; i++ )
		trap->AddCommand( commands[i].cmd );

	//
	// the game server will interpret these commands, which will be automatically
	// forwarded to the server after they are not recognized locally
	//
	for( i = 0; i < numgcmds; i++ )
		trap->AddCommand( gcmds[i] );
}

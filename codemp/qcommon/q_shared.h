#pragma once

#include <omp.h>
#include "../game/bg_weapons.h"
#include "../qcommon/inifile.h"

// Copyright (C) 1999-2000 Id Software, Inc.
//

// q_shared.h -- included first by ALL program modules.
// A user mod should never modify this file

//#define __DEBUG_ZALLOC__

#define __ENABLE_DEDICATED_CONSOLE_COLORS__			// Enable color on dedicated console...

#define __MMO__
//#define __AAS_AI_TESTING__
//#define __USE_NAVMESH__
//#define __USE_NAVLIB__
//#define __NPC_DYNAMIC_THREADS__					// New version of threading AI... Experimental...
#define __NO_ICARUS__								// Fuck this shit...
#define ___ALLOW_ANY_GLM___							// Disables checks on GLM models...
#define __NPCS_USE_BG_ANIMS__						// Force NPCs to not use NPC code humanoid animations...
#define __NPC_CPU_USAGE_TWEAKS__					// Enable experimental NPC cpu usage tweaks...
#define __FULL_VERSION_WEAPONS__					// Enable after development (increases map load times)...
//#define __PRECACHE_NPCS__							// Enable after development to reduce ingame lag (increases map load times)...
#define __TIMED_STAGGER__
//#define __ENGINE_AWESOMIUM__
#define __PLAYER_VEHICLES__							// Enable player vehicles system...
//#define __ROLL_EVASION_TRACES__					// Enable this if NPCs fall of things too much... With events they shouldn't...
//#define __CLIMBING__								// Climb up rocks or trees...

// Disable stupid warnings...
#pragma warning( disable : 4996 )

#define PRODUCT_NAME			"Warzone"

#define CLIENT_WINDOW_TITLE "Star Wars: Warzone"
#define CLIENT_CONSOLE_TITLE "Warzone Console"
#define HOMEPATH_NAME_UNIX "warzone"
#define HOMEPATH_NAME_WIN "warzone"
#define HOMEPATH_NAME_MACOSX HOMEPATH_NAME_WIN

#define	BASEGAME "base"

//Toggle bit for shots remaining.Just like in JK2 with anims
#define SHOTS_TOGGLEBIT (1 << 7)

//NOTENOTE: Only change this to re-point ICARUS to a new script directory
#define Q3_SCRIPT_DIR	"scripts"

#define MAX_TEAMNAME 32
#define MAX_MASTER_SERVERS      5	// number of supported master servers

#define BASE_COMPAT // some unused and leftover code has been stripped out, but this breaks compatibility
					//	between base<->modbase clients and servers (mismatching events, powerups, etc)
					// leave this defined to ensure compatibility

#include "qcommon/disablewarnings.h"

#include "game/teams.h" //npc team stuff

#define MAX_WORLD_COORD		(524288)//( 64 * 1024 )
#define MIN_WORLD_COORD		-(524288)//( -64 * 1024 )
#define WORLD_SIZE			( MAX_WORLD_COORD - MIN_WORLD_COORD )

//Pointer safety utilities
#define VALID( a )		( a != NULL )
#define	VALIDATE( a )	( assert( a ) )

#define	VALIDATEV( a )	if ( a == NULL ) {	assert(0);	return;			}
#define	VALIDATEB( a )	if ( a == NULL ) {	assert(0);	return qfalse;	}
#define VALIDATEP( a )	if ( a == NULL ) {	assert(0);	return NULL;	}

#define VALIDSTRING( a )	( ( a != NULL ) && ( a[0] != '\0' ) )
#define VALIDENT( e )		( ( e != NULL ) && ( (e)->inuse ) )

#define ARRAY_LEN( x ) ( sizeof( x ) / sizeof( *(x) ) )
#define STRING( a ) #a
#define XSTRING( a ) STRING( a )
/*
#define G2_EHNANCEMENTS

#ifdef G2_EHNANCEMENTS
//these two will probably explode if they're defined independent of one another.
//rww - RAGDOLL_BEGIN
#define JK2_RAGDOLL
//rww - RAGDOLL_END
//rww - Bone cache for multiplayer base.
#define MP_BONECACHE
#endif
*/

#ifndef FINAL_BUILD
	// may want to enable timing and leak checking again. requires G2API changes.
//	#define G2_PERFORMANCE_ANALYSIS
//	#define _FULL_G2_LEAK_CHECKING
//	extern int g_Ghoul2Allocations;
//	extern int g_G2ServerAlloc;
//	extern int g_G2ClientAlloc;
//	extern int g_G2AllocServer;
#endif

#include <assert.h>
#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <stddef.h>

//Ignore __attribute__ on non-gcc platforms
#if !defined(__GNUC__) && !defined(__attribute__)
	#define __attribute__(x)
#endif

#if defined(__GNUC__)
	#define UNUSED_VAR __attribute__((unused))
#else
	#define UNUSED_VAR
#endif

#if (defined _MSC_VER)
	#define Q_EXPORT __declspec(dllexport)
#elif (defined __SUNPRO_C)
	#define Q_EXPORT __global
#elif ((__GNUC__ >= 3) && (!__EMX__) && (!sun))
	#define Q_EXPORT __attribute__((visibility("default")))
#else
	#define Q_EXPORT
#endif

// this is the define for determining if we have an asm version of a C function
#if (defined(_M_IX86) || defined(__i386__)) && !defined(__sun__)
	#define id386	1
#else
	#define id386	0
#endif

#if (defined(powerc) || defined(powerpc) || defined(ppc) || defined(__ppc) || defined(__ppc__)) && !defined(C_ONLY)
	#define idppc	1
#else
	#define idppc	0
#endif

short ShortSwap( short l );
int LongSwap( int l );
float FloatSwap( const float *f );


#include "qcommon/q_platform.h"

// ================================================================
// TYPE DEFINITIONS
// ================================================================

typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long ulong;

typedef enum qboolean_e { qfalse=0, qtrue } qboolean;

#ifndef min
	#define min(x,y) ((x)<(y)?(x):(y))
#endif
#ifndef max
	#define max(x,y) ((x)>(y)?(x):(y))
#endif

#define Q_min(x,y) ((x)<(y)?(x):(y))
#define Q_max(x,y) ((x)>(y)?(x):(y))

#if defined (_MSC_VER) && (_MSC_VER >= 1600)

	#include <stdint.h>

	// vsnprintf is ISO/IEC 9899:1999
	// abstracting this to make it portable
	int Q_vsnprintf( char *str, size_t size, const char *format, va_list args );

#elif defined (_MSC_VER)

	#include <io.h>

	typedef signed __int64 int64_t;
	typedef signed __int32 int32_t;
	typedef signed __int16 int16_t;
	typedef signed __int8  int8_t;
	typedef unsigned __int64 uint64_t;
	typedef unsigned __int32 uint32_t;
	typedef unsigned __int16 uint16_t;
	typedef unsigned __int8  uint8_t;

	// vsnprintf is ISO/IEC 9899:1999
	// abstracting this to make it portable
	int Q_vsnprintf( char *str, size_t size, const char *format, va_list args );
#else // not using MSVC

	#include <stdint.h>

	#define Q_vsnprintf vsnprintf

#endif

// 32 bit field aliasing
typedef union byteAlias_u {
	float f;
	int32_t i;
	uint32_t ui;
	qboolean qb;
	byte b[4];
	char c[4];
} byteAlias_t;

typedef union fileBuffer_u {
	void *v;
	char *c;
	byte *b;
} fileBuffer_t;

typedef int32_t qhandle_t, thandle_t, fxHandle_t, sfxHandle_t, fileHandle_t, clipHandle_t;

#define NULL_HANDLE ((qhandle_t)0)
#define NULL_SOUND ((sfxHandle_t)0)
#define NULL_FX ((fxHandle_t)0)
#define NULL_SFX ((sfxHandle_t)0)
#define NULL_FILE ((fileHandle_t)0)
#define NULL_CLIP ((clipHandle_t)0)

#define PAD(base, alignment)	(((base)+(alignment)-1) & ~((alignment)-1))
#define PADLEN(base, alignment)	(PAD((base), (alignment)) - (base))

#define PADP(base, alignment)	((void *) PAD((intptr_t) (base), (alignment)))

#ifdef __GNUC__
#define QALIGN(x) __attribute__((aligned(x)))
#else
#define QALIGN(x)
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#define	MAX_QINT			0x7fffffff
#define	MIN_QINT			(-MAX_QINT-1)

#define INT_ID( a, b, c, d ) (uint32_t)((((d) & 0xff) << 24) | (((c) & 0xff) << 16) | (((b) & 0xff) << 8) | ((a) & 0xff))

// angle indexes
#define	PITCH				0		// up / down
#define	YAW					1		// left / right
#define	ROLL				2		// fall over

// the game guarantees that no string from the network will ever
// exceed MAX_STRING_CHARS
#define	MAX_STRING_CHARS	1024	// max length of a string passed to Cmd_TokenizeString
#define	MAX_STRING_TOKENS	1024	// max tokens resulting from Cmd_TokenizeString
#define	MAX_TOKEN_CHARS		1024	// max length of an individual token

#define	MAX_INFO_STRING		1024
#define	MAX_INFO_KEY		1024
#define	MAX_INFO_VALUE		1024

#define	BIG_INFO_STRING		8192  // used for system info key only
#define	BIG_INFO_KEY		  8192
#define	BIG_INFO_VALUE		8192

#define NET_ADDRSTRMAXLEN 48 // maximum length of an IPv6 address string including trailing '\0'

// moved these from ui_local.h so we can access them everywhere
#define MAX_ADDRESSLENGTH		256//64
#define MAX_HOSTNAMELENGTH		256//22
#define MAX_MAPNAMELENGTH		256//16
#define MAX_STATUSLENGTH		256//64

#define	MAX_QPATH			64		// max length of a quake game pathname
#ifdef PATH_MAX
#define MAX_OSPATH			PATH_MAX
#else
#define	MAX_OSPATH			256		// max length of a filesystem pathname
#endif

#define	MAX_NAME_LENGTH		32		// max length of a client name
#define MAX_NETNAME			36

#define	MAX_SAY_TEXT	150

// paramters for command buffer stuffing
typedef enum {
	EXEC_NOW,			// don't return until completed, a VM should NEVER use this,
						// because some commands might cause the VM to be unloaded...
	EXEC_INSERT,		// insert at current position, but don't run yet
	EXEC_APPEND			// add to end of the command buffer (normal case)
} cbufExec_t;


//
// these aren't needed by any of the VMs.  put in another header?
//
#define	MAX_MAP_AREA_BYTES		32		// bit vector of area visibility


#define LS_STYLES_START			0
#define LS_NUM_STYLES			32
#define	LS_SWITCH_START			(LS_STYLES_START+LS_NUM_STYLES)
#define LS_NUM_SWITCH			32
#if !defined MAX_LIGHT_STYLES
#define MAX_LIGHT_STYLES		64
#endif

//For system-wide prints
enum WL_e {
	WL_ERROR=1,
	WL_WARNING,
	WL_VERBOSE,
	WL_DEBUG
};

extern float forceSpeedLevels[4];

// print levels from renderer (FIXME: set up for game / cgame?)
typedef enum {
	PRINT_ALL,
	PRINT_DEVELOPER,		// only print when "developer 1"
	PRINT_WARNING,
	PRINT_ERROR
} printParm_t;


#ifdef ERR_FATAL
#undef ERR_FATAL			// this is be defined in malloc.h
#endif

// parameters to the main Error routine
typedef enum {
	ERR_FATAL,					// exit the entire game with a popup window
	ERR_DROP,					// print to console and disconnect from game
	ERR_SERVERDISCONNECT,		// don't kill server
	ERR_DISCONNECT,				// client disconnected from the server
	ERR_NEED_CD					// pop up the need-cd dialog
} errorParm_t;


// font rendering values used by ui and cgame

/*#define PROP_GAP_WIDTH			3
#define PROP_SPACE_WIDTH		8
#define PROP_HEIGHT				27
#define PROP_SMALL_SIZE_SCALE	0.75*/

#define PROP_GAP_WIDTH			2 // 3
#define PROP_SPACE_WIDTH		4
#define PROP_HEIGHT				16

#define PROP_TINY_SIZE_SCALE	1
#define PROP_SMALL_SIZE_SCALE	1
#define PROP_BIG_SIZE_SCALE		1
#define PROP_GIANT_SIZE_SCALE	2

#define PROP_TINY_HEIGHT		10
#define PROP_GAP_TINY_WIDTH		1
#define PROP_SPACE_TINY_WIDTH	3

#define PROP_BIG_HEIGHT			24
#define PROP_GAP_BIG_WIDTH		3
#define PROP_SPACE_BIG_WIDTH	6

#define BLINK_DIVISOR			200
#define PULSE_DIVISOR			75

#define UI_LEFT			0x00000000	// default
#define UI_CENTER		0x00000001
#define UI_RIGHT		0x00000002
#define UI_FORMATMASK	0x00000007
#define UI_SMALLFONT	0x00000010
#define UI_BIGFONT		0x00000020	// default

#define UI_DROPSHADOW	0x00000800
#define UI_BLINK		0x00001000
#define UI_INVERSE		0x00002000
#define UI_PULSE		0x00004000

#if defined(_DEBUG) && !defined(BSPC)
	#define HUNK_DEBUG
#endif

typedef enum {
	h_high,
	h_low,
	h_dontcare
} ha_pref;

void *Hunk_Alloc( int size, ha_pref preference );

#define Com_Memset memset
#define Com_Memcpy memcpy

#define CIN_system	1
#define CIN_loop	2
#define	CIN_hold	4
#define CIN_silent	8
#define CIN_shader	16

/*
==============================================================

MATHLIB

==============================================================
*/


#define vec_t	float
#define ivec_t	int

typedef float	vec2_t[2], vec3_t[3], vec4_t[4], vec5_t[5];
typedef int		ivec2_t[2],	ivec3_t[3],	ivec4_t[4],	ivec5_t[5];
typedef vec3_t	vec3pair_t[2], matrix3_t[3];

typedef	int	fixed4_t, fixed8_t, fixed16_t;

#ifndef M_PI
#define M_PI		3.14159265358979323846f	// matches value in gcc v2 math.h
#endif

#if defined(_MSC_VER)
static __inline long Q_ftol(float f)
{
	return (long)f;
}
#else
static inline long Q_ftol(float f)
{
	return (long)f;
}
#endif


typedef enum {
	BLK_NO,
	BLK_TIGHT,		// Block only attacks and shots around the saber itself, a bbox of around 12x12x12
	BLK_WIDE		// Block all attacks in an area around the player in a rough arc of 180 degrees
} saberBlockType_t;

typedef enum {
	BLOCKED_NONE,
	BLOCKED_BOUNCE_MOVE,
	BLOCKED_PARRY_BROKEN,
	BLOCKED_ATK_BOUNCE,
	BLOCKED_UPPER_RIGHT,
	BLOCKED_UPPER_LEFT,
	BLOCKED_LOWER_RIGHT,
	BLOCKED_LOWER_LEFT,
	BLOCKED_TOP,
	BLOCKED_UPPER_RIGHT_PROJ,
	BLOCKED_UPPER_LEFT_PROJ,
	BLOCKED_LOWER_RIGHT_PROJ,
	BLOCKED_LOWER_LEFT_PROJ,
	BLOCKED_TOP_PROJ,
	BLOCKED_LIGHTNING,
} saberBlockedType_t;



typedef enum
{
	SABER_RED,
	SABER_ORANGE,
	SABER_YELLOW,
	SABER_GREEN,
	SABER_BLUE,
	SABER_PURPLE,
	//[RGBSabers]
	SABER_WHITE,
	SABER_BLACK,
	SABER_RGB,
	SABER_PIMP,
	SABER_SCRIPTED,
	//[/RGBSabers]
	NUM_SABER_COLORS
} saber_colors_t;

typedef enum
{
	FP_FIRST = 0,//marker
	FP_HEAL = 0,//instant
	FP_LEVITATION,//hold/duration
	FP_SPEED,//duration
	FP_PUSH,//hold/duration
	FP_PULL,//hold/duration
	FP_TELEPATHY,//instant
	FP_GRIP,//hold/duration
	FP_LIGHTNING,//hold/duration
	FP_RAGE,//duration
	FP_PROTECT,
	FP_ABSORB,
	FP_TEAM_HEAL,
	FP_TEAM_FORCE,
	FP_DRAIN,
	FP_SEE,
	FP_SABER_OFFENSE,
	FP_SABER_DEFENSE,
	FP_SABERTHROW,
	NUM_FORCE_POWERS
} forcePowers_t;

typedef enum forcePowerLevels_e {
	FORCE_LEVEL_0,
	FORCE_LEVEL_1,
	FORCE_LEVEL_2,
	FORCE_LEVEL_3,
	NUM_FORCE_POWER_LEVELS
} forcePowerLevels_t;

#define	FORCE_LEVEL_4 (FORCE_LEVEL_3+1)
#define	FORCE_LEVEL_5 (FORCE_LEVEL_4+1)

//rww - a C-ified structure version of the class which fires off callbacks and gives arguments to update ragdoll status.
enum sharedERagPhase
{
	RP_START_DEATH_ANIM,
	RP_END_DEATH_ANIM,
	RP_DEATH_COLLISION,
	RP_CORPSE_SHOT,
	RP_GET_PELVIS_OFFSET,  // this actually does nothing but set the pelvisAnglesOffset, and pelvisPositionOffset
	RP_SET_PELVIS_OFFSET,  // this actually does nothing but set the pelvisAnglesOffset, and pelvisPositionOffset
	RP_DISABLE_EFFECTORS  // this removes effectors given by the effectorsToTurnOff member
};

enum sharedERagEffector
{
	RE_MODEL_ROOT=			0x00000001, //"model_root"
	RE_PELVIS=				0x00000002, //"pelvis"
	RE_LOWER_LUMBAR=		0x00000004, //"lower_lumbar"
	RE_UPPER_LUMBAR=		0x00000008, //"upper_lumbar"
	RE_THORACIC=			0x00000010, //"thoracic"
	RE_CRANIUM=				0x00000020, //"cranium"
	RE_RHUMEROUS=			0x00000040, //"rhumerus"
	RE_LHUMEROUS=			0x00000080, //"lhumerus"
	RE_RRADIUS=				0x00000100, //"rradius"
	RE_LRADIUS=				0x00000200, //"lradius"
	RE_RFEMURYZ=			0x00000400, //"rfemurYZ"
	RE_LFEMURYZ=			0x00000800, //"lfemurYZ"
	RE_RTIBIA=				0x00001000, //"rtibia"
	RE_LTIBIA=				0x00002000, //"ltibia"
	RE_RHAND=				0x00004000, //"rhand"
	RE_LHAND=				0x00008000, //"lhand"
	RE_RTARSAL=				0x00010000, //"rtarsal"
	RE_LTARSAL=				0x00020000, //"ltarsal"
	RE_RTALUS=				0x00040000, //"rtalus"
	RE_LTALUS=				0x00080000, //"ltalus"
	RE_RRADIUSX=			0x00100000, //"rradiusX"
	RE_LRADIUSX=			0x00200000, //"lradiusX"
	RE_RFEMURX=				0x00400000, //"rfemurX"
	RE_LFEMURX=				0x00800000, //"lfemurX"
	RE_CEYEBROW=			0x01000000 //"ceyebrow"
};

typedef struct sharedRagDollParams_s {
	vec3_t angles;
	vec3_t position;
	vec3_t scale;
	vec3_t pelvisAnglesOffset;    // always set on return, an argument for RP_SET_PELVIS_OFFSET
	vec3_t pelvisPositionOffset; // always set on return, an argument for RP_SET_PELVIS_OFFSET

	float fImpactStrength; //should be applicable when RagPhase is RP_DEATH_COLLISION
	float fShotStrength; //should be applicable for setting velocity of corpse on shot (probably only on RP_CORPSE_SHOT)
	int me; //index of entity giving this update

	//rww - we have convenient animation/frame access in the game, so just send this info over from there.
	int startFrame;
	int endFrame;

	int collisionType; // 1 = from a fall, 0 from effectors, this will be going away soon, hence no enum

	qboolean CallRagDollBegin; // a return value, means that we are now begininng ragdoll and the NPC stuff needs to happen

	int RagPhase;

// effector control, used for RP_DISABLE_EFFECTORS call

	int effectorsToTurnOff;  // set this to an | of the above flags for a RP_DISABLE_EFFECTORS

} sharedRagDollParams_t;

//And one for updating during model animation.
typedef struct sharedRagDollUpdateParams_s {
	vec3_t angles;
	vec3_t position;
	vec3_t scale;
	vec3_t velocity;
	int	me;
	int settleFrame;
} sharedRagDollUpdateParams_t;

//rww - update parms for ik bone stuff
typedef struct sharedIKMoveParams_s {
	char boneName[512]; //name of bone
	vec3_t desiredOrigin; //world coordinate that this bone should be attempting to reach
	vec3_t origin; //world coordinate of the entity who owns the g2 instance that owns the bone
	float movementSpeed; //how fast the bone should move toward the destination
} sharedIKMoveParams_t;


typedef struct sharedSetBoneIKStateParams_s {
	vec3_t pcjMins; //ik joint limit
	vec3_t pcjMaxs; //ik joint limit
	vec3_t origin; //origin of caller
	vec3_t angles; //angles of caller
	vec3_t scale; //scale of caller
	float radius; //bone rad
	int blendTime; //bone blend time
	int pcjOverrides; //override ik bone flags
	int startFrame; //base pose start
	int endFrame; //base pose end
	qboolean forceAnimOnBone; //normally if the bone has specified start/end frames already it will leave it alone.. if this is true, then the animation will be restarted on the bone with the specified frames anyway.
} sharedSetBoneIKStateParams_t;

enum sharedEIKMoveState
{
	IKS_NONE = 0,
	IKS_DYNAMIC
};

//material stuff needs to be shared
typedef enum //# material_e
{
	MAT_METAL = 0,	// scorched blue-grey metal
	MAT_GLASS,		// not a real chunk type, just plays an effect with glass sprites
	MAT_ELECTRICAL,	// sparks only
	MAT_ELEC_METAL,	// sparks/electrical type metal
	MAT_DRK_STONE,	// brown
	MAT_LT_STONE,	// tan
	MAT_GLASS_METAL,// glass sprites and METAl chunk
	MAT_METAL2,		// electrical metal type
	MAT_NONE,		// no chunks
	MAT_GREY_STONE,	// grey
	MAT_METAL3,		// METAL and METAL2 chunks
	MAT_CRATE1,		// yellow multi-colored crate chunks
	MAT_GRATE1,		// grate chunks
	MAT_ROPE,		// for yavin trial...no chunks, just wispy bits
	MAT_CRATE2,		// read multi-colored crate chunks
	MAT_WHITE_METAL,// white angular chunks
	MAT_SNOWY_ROCK,	// gray & brown chunks

	NUM_MATERIALS
} material_t;

//rww - bot stuff that needs to be shared
//#define MAX_WPARRAY_SIZE 1048576
//#define MAX_WPARRAY_SIZE 524288
#define MAX_WPARRAY_SIZE 131072
//#define MAX_WPARRAY_SIZE 65536
//#define MAX_WPARRAY_SIZE 32000
//#define MAX_WPARRAY_SIZE 4096
#define MAX_NEIGHBOR_SIZE 32
//#define MAX_NEIGHBOR_SIZE 64

#define MAX_NEIGHBOR_LINK_DISTANCE 128
#define MAX_NEIGHBOR_FORCEJUMP_LINK_DISTANCE 400

#define DEFAULT_GRID_SPACING 400

typedef struct wpneighbor_s
{
	int num;
	int forceJumpTo;
	int cost;
} wpneighbor_t;

typedef struct wpobject_s
{
	bool inuse;
	int index;
	vec3_t origin;
	int flags;

	bool wpIsBadChecked;
	bool wpIsBad;

	int neighbornum;
	wpneighbor_t neighbors[MAX_NEIGHBOR_SIZE];
} wpobject_t;


#define NUMVERTEXNORMALS	162
extern	vec3_t	bytedirs[NUMVERTEXNORMALS];

// all drawing is done to a 640*480 virtual screen size
// and will be automatically scaled to the real resolution
#define	SCREEN_WIDTH		640
#define	SCREEN_HEIGHT		480

#define TINYCHAR_WIDTH		(SMALLCHAR_WIDTH)
#define TINYCHAR_HEIGHT		(SMALLCHAR_HEIGHT/2)

#define SMALLCHAR_WIDTH		8
#define SMALLCHAR_HEIGHT	16

#define BIGCHAR_WIDTH		16
#define BIGCHAR_HEIGHT		16

#define	GIANTCHAR_WIDTH		32
#define	GIANTCHAR_HEIGHT	48

typedef enum
{
CT_NONE,
CT_BLACK,
CT_RED,
CT_GREEN,
CT_BLUE,
CT_YELLOW,
CT_MAGENTA,
CT_CYAN,
CT_WHITE,
CT_LTGREY,
CT_MDGREY,
CT_DKGREY,
CT_DKGREY2,

CT_VLTORANGE,
CT_LTORANGE,
CT_DKORANGE,
CT_VDKORANGE,

CT_VLTBLUE1,
CT_LTBLUE1,
CT_DKBLUE1,
CT_VDKBLUE1,

CT_VLTBLUE2,
CT_LTBLUE2,
CT_DKBLUE2,
CT_VDKBLUE2,

CT_VLTBROWN1,
CT_LTBROWN1,
CT_DKBROWN1,
CT_VDKBROWN1,

CT_VLTGOLD1,
CT_LTGOLD1,
CT_DKGOLD1,
CT_VDKGOLD1,

CT_VLTPURPLE1,
CT_LTPURPLE1,
CT_DKPURPLE1,
CT_VDKPURPLE1,

CT_VLTPURPLE2,
CT_LTPURPLE2,
CT_DKPURPLE2,
CT_VDKPURPLE2,

CT_VLTPURPLE3,
CT_LTPURPLE3,
CT_DKPURPLE3,
CT_VDKPURPLE3,

CT_VLTRED1,
CT_LTRED1,
CT_DKRED1,
CT_VDKRED1,
CT_VDKRED,
CT_DKRED,

CT_VLTAQUA,
CT_LTAQUA,
CT_DKAQUA,
CT_VDKAQUA,

CT_LTPINK,
CT_DKPINK,
CT_LTCYAN,
CT_DKCYAN,
CT_LTBLUE3,
CT_BLUE3,
CT_DKBLUE3,

CT_HUD_GREEN,
CT_HUD_RED,
CT_ICON_BLUE,
CT_NO_AMMO_RED,
CT_HUD_ORANGE,

CT_MAX
} ct_table_t;

extern vec4_t colorTable[CT_MAX];

extern	vec4_t		colorBlack;
extern	vec4_t		colorRed;
extern	vec4_t		colorGreen;
extern	vec4_t		colorBlue;
extern	vec4_t		colorYellow;
extern	vec4_t		colorOrange;
extern	vec4_t		colorMagenta;
extern	vec4_t		colorCyan;
extern	vec4_t		colorWhite;
extern	vec4_t		colorLtGrey;
extern	vec4_t		colorMdGrey;
extern	vec4_t		colorDkGrey;
extern	vec4_t		colorLtBlue;
extern	vec4_t		colorDkBlue;

#define Q_COLOR_ESCAPE	'^'
#define Q_COLOR_BITS 0xF // was 7

// you MUST have the last bit on here about colour strings being less than 7 or taiwanese strings register as colour!!!!
#define Q_IsColorString(p)	( p && *(p) == Q_COLOR_ESCAPE && *((p)+1) && *((p)+1) != Q_COLOR_ESCAPE && *((p)+1) <= '9' && *((p)+1) >= '0' )
// Correct version of the above for Q_StripColor
#define Q_IsColorStringExt(p)	((p) && *(p) == Q_COLOR_ESCAPE && *((p)+1) && *((p)+1) >= '0' && *((p)+1) <= '9') // ^[0-9]


#define COLOR_BLACK		'0'
#define COLOR_RED		'1'
#define COLOR_GREEN		'2'
#define COLOR_YELLOW	'3'
#define COLOR_BLUE		'4'
#define COLOR_CYAN		'5'
#define COLOR_MAGENTA	'6'
#define COLOR_WHITE		'7'
#define COLOR_ORANGE	'8'
#define COLOR_GREY		'9'
#define ColorIndex(c)	( ( (c) - '0' ) & Q_COLOR_BITS )

#define S_COLOR_BLACK	"^0"
#define S_COLOR_RED		"^1"
#define S_COLOR_GREEN	"^2"
#define S_COLOR_YELLOW	"^3"
#define S_COLOR_BLUE	"^4"
#define S_COLOR_CYAN	"^5"
#define S_COLOR_MAGENTA	"^6"
#define S_COLOR_WHITE	"^7"
#define S_COLOR_ORANGE	"^8"
#define S_COLOR_GREY	"^9"

extern vec4_t g_color_table[Q_COLOR_BITS+1];

#define	MAKERGB( v, r, g, b ) v[0]=r;v[1]=g;v[2]=b
#define	MAKERGBA( v, r, g, b, a ) v[0]=r;v[1]=g;v[2]=b;v[3]=a

struct cplane_s;

extern	vec3_t		vec3_origin;
extern	matrix3_t	axisDefault;

#if idppc

static inline float Q_rsqrt( float number ) {
		float x = 0.5f * number;
                float y;
#ifdef __GNUC__
                asm("frsqrte %0,%1" : "=f" (y) : "f" (number));
#else
		y = __frsqrte( number );
#endif
		return y * (1.5f - (x * y * y));
	}

#ifdef __GNUC__
static inline float Q_fabs(float x) {
    float abs_x;

    asm("fabs %0,%1" : "=f" (abs_x) : "f" (x));
    return abs_x;
}
#else
#define Q_fabs __fabsf
#endif

#else

float Q_fabs( float f );
float Q_rsqrt( float f );		// reciprocal square root

#endif // idppc


#define SQRTFAST( x ) ( (x) * Q_rsqrt( x ) )

signed char ClampChar( int i );
signed short ClampShort( int i );

float Q_powf ( float x, int y );

// this isn't a real cheap function to call!
int DirToByte( vec3_t dir );
void ByteToDir( int b, vec3_t dir );

//rwwRMG - added math defines
#define minimum( x, y ) ((x) < (y) ? (x) : (y))
#define maximum( x, y ) ((x) > (y) ? (x) : (y))

#define DEG2RAD( deg ) ( ((deg)*M_PI) / 180.0f )
#define RAD2DEG( rad ) ( ((rad)*180.0f) / M_PI )

void		VectorAdd( const vec3_t vec1, const vec3_t vec2, vec3_t vecOut );
void		VectorSubtract( const vec3_t vec1, const vec3_t vec2, vec3_t vecOut );
void		VectorScale( const vec3_t vecIn, float scale, vec3_t vecOut );
void		VectorScale4( const vec4_t vecIn, float scale, vec4_t vecOut );
void		VectorMA( const vec3_t vec1, float scale, const vec3_t vec2, vec3_t vecOut );
float		VectorLength( const vec3_t vec );
float		VectorLengthSquared( const vec3_t vec );
float		Distance( const vec3_t p1, const vec3_t p2 );
float		DistanceSquared( const vec3_t p1, const vec3_t p2 );
void		VectorNormalizeFast( vec3_t vec );
float		VectorNormalize( vec3_t vec );
float		VectorNormalize2( const vec3_t vec, vec3_t vecOut );
void		VectorCopy( const vec3_t vecIn, vec3_t vecOut );
void		VectorCopy4( const vec4_t vecIn, vec4_t vecOut );
void		VectorSet( vec3_t vec, float x, float y, float z );
void		VectorSet4( vec4_t vec, float x, float y, float z, float w );
void		VectorSet5( vec5_t vec, float x, float y, float z, float w, float u );
void		VectorClear( vec3_t vec );
void		VectorClear4( vec4_t vec );
void		VectorInc( vec3_t vec );
void		VectorDec( vec3_t vec );
void		VectorInverse( vec3_t vec );
void		CrossProduct( const vec3_t vec1, const vec3_t vec2, vec3_t vecOut );
float		DotProduct( const vec3_t vec1, const vec3_t vec2 );
qboolean	VectorCompare( const vec3_t vec1, const vec3_t vec2 );
qboolean	VectorCompare2(const vec3_t v1, const vec3_t v2);
void		SnapVector( float *v );

#define		VectorAddM( vec1, vec2, vecOut )		((vecOut)[0]=(vec1)[0]+(vec2)[0], (vecOut)[1]=(vec1)[1]+(vec2)[1], (vecOut)[2]=(vec1)[2]+(vec2)[2])
#define		VectorSubtractM( vec1, vec2, vecOut )	((vecOut)[0]=(vec1)[0]-(vec2)[0], (vecOut)[1]=(vec1)[1]-(vec2)[1], (vecOut)[2]=(vec1)[2]-(vec2)[2])
#define		VectorScaleM( vecIn, scale, vecOut )	((vecOut)[0]=(vecIn)[0]*(scale), (vecOut)[1]=(vecIn)[1]*(scale), (vecOut)[2]=(vecIn)[2]*(scale))
#define		VectorScale4M( vecIn, scale, vecOut )	((vecOut)[0]=(vecIn)[0]*(scale), (vecOut)[1]=(vecIn)[1]*(scale), (vecOut)[2]=(vecIn)[2]*(scale), (vecOut)[3]=(vecIn)[3]*(scale))
#define		VectorMAM( vec1, scale, vec2, vecOut )	((vecOut)[0]=(vec1)[0]+(vec2)[0]*(scale), (vecOut)[1]=(vec1)[1]+(vec2)[1]*(scale), (vecOut)[2]=(vec1)[2]+(vec2)[2]*(scale))
#define		VectorLengthM( vec )					VectorLength( vec )
#define		VectorLengthSquaredM( vec )				VectorLengthSquared( vec )
#define		DistanceM( vec )						Distance( vec )
#define		DistanceSquaredM( p1, p2 )				DistanceSquared( p1, p2 )
#define		VectorNormalizeFastM( vec )				VectorNormalizeFast( vec )
#define		VectorNormalizeM( vec )					VectorNormalize( vec )
#define		VectorNormalize2M( vec, vecOut )		VectorNormalize2( vec, vecOut )
#define		VectorCopyM( vecIn, vecOut )			((vecOut)[0]=(vecIn)[0], (vecOut)[1]=(vecIn)[1], (vecOut)[2]=(vecIn)[2])
#define		VectorCopy4M( vecIn, vecOut )			((vecOut)[0]=(vecIn)[0], (vecOut)[1]=(vecIn)[1], (vecOut)[2]=(vecIn)[2], (vecOut)[3]=(vecIn)[3])
#define		VectorSetM( vec, x, y, z )				((vec)[0]=(x), (vec)[1]=(y), (vec)[2]=(z))
#define		VectorSet4M( vec, x, y, z, w )			((vec)[0]=(x), (vec)[1]=(y), (vec)[2]=(z), (vec)[3]=(w))
#define		VectorSet5M( vec, x, y, z, w, u )		((vec)[0]=(x), (vec)[1]=(y), (vec)[2]=(z), (vec)[3]=(w), (vec)[4]=(u))
#define		VectorClearM( vec )						((vec)[0]=(vec)[1]=(vec)[2]=0)
#define		VectorClear4M( vec )					((vec)[0]=(vec)[1]=(vec)[2]=(vec)[3]=0)
#define		VectorIncM( vec )						((vec)[0]+=1.0f, (vec)[1]+=1.0f, (vec)[2]+=1.0f)
#define		VectorDecM( vec )						((vec)[0]-=1.0f, (vec)[1]-=1.0f, (vec)[2]-=1.0f)
#define		VectorInverseM( vec )					((vec)[0]=-(vec)[0], (vec)[1]=-(vec)[1], (vec)[2]=-(vec)[2])
#define		CrossProductM( vec1, vec2, vecOut )		((vecOut)[0]=((vec1)[1]*(vec2)[2])-((vec1)[2]*(v2)[1]), (vecOut)[1]=((vec1)[2]*(vec2)[0])-((vec1)[0]*(vec2)[2]), (vecOut)[2]=((vec1)[0]*(vec2)[1])-((vec1)[1]*(vec2)[0]))
#define		DotProductM( x, y )						((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define		VectorCompareM( vec1, vec2 )			(!!((vec1)[0]==(vec2)[0] && (vec1)[1]==(vec2)[1] && (vec1)[2]==(vec2)[2]))

// TODO
#define VectorScaleVector(a,b,c)		(((c)[0]=(a)[0]*(b)[0]),((c)[1]=(a)[1]*(b)[1]),((c)[2]=(a)[2]*(b)[2]))
#define VectorInverseScaleVector(a,b,c)	((c)[0]=(a)[0]/(b)[0],(c)[1]=(a)[1]/(b)[1],(c)[2]=(a)[2]/(b)[2])
#define VectorScaleVectorAdd(c,a,b,o)	((o)[0]=(c)[0]+((a)[0]*(b)[0]),(o)[1]=(c)[1]+((a)[1]*(b)[1]),(o)[2]=(c)[2]+((a)[2]*(b)[2]))
#define VectorAdvance(a,s,b,c)			(((c)[0]=(a)[0] + s * ((b)[0] - (a)[0])),((c)[1]=(a)[1] + s * ((b)[1] - (a)[1])),((c)[2]=(a)[2] + s * ((b)[2] - (a)[2])))
#define VectorAverage(a,b,c)			(((c)[0]=((a)[0]+(b)[0])*0.5f),((c)[1]=((a)[1]+(b)[1])*0.5f),((c)[2]=((a)[2]+(b)[2])*0.5f))
#define VectorNegate(a,b)				((b)[0]=-(a)[0],(b)[1]=-(a)[1],(b)[2]=-(a)[2])

unsigned ColorBytes3 (float r, float g, float b);
unsigned ColorBytes4 (float r, float g, float b, float a);

float NormalizeColor( const vec3_t in, vec3_t out );

float RadiusFromBounds( const vec3_t mins, const vec3_t maxs );
void ClearBounds( vec3_t mins, vec3_t maxs );
float DistanceHorizontal( const vec3_t p1, const vec3_t p2 );
float DistanceHorizontalSquared( const vec3_t p1, const vec3_t p2 );
float DistanceVertical( const vec3_t p1, const vec3_t p2 );
float DistanceVerticalSquared( const vec3_t p1, const vec3_t p2 );
void AddPointToBounds( const vec3_t v, vec3_t mins, vec3_t maxs );
void VectorRotate( const vec3_t in, matrix3_t matrix, vec3_t out );
int Q_log2(int val);

qboolean Q_isnan(float f);
float Q_acos(float c);
float Q_asin(float c);

int		Q_rand( int *seed );
float	Q_random( int *seed );
float	Q_crandom( int *seed );

#define random()	((rand () & 0x7fff) / ((float)0x7fff))
#define crandom()	(2.0 * (random() - 0.5))

void vectoangles( const vec3_t value1, vec3_t angles);
void AnglesToAxis( const vec3_t angles, matrix3_t axis );
void AxisToAngles( vec3_t axis[3], vec3_t angles );

void AxisClear( matrix3_t axis );
void AxisCopy( matrix3_t in, matrix3_t out );

void SetPlaneSignbits( struct cplane_s *out );
int BoxOnPlaneSide (vec3_t emins, vec3_t emaxs, struct cplane_s *plane);

double	fmod( double x, double y );
float	AngleMod(float a);
float	LerpAngle (float from, float to, float frac);
float	AngleSubtract( float a1, float a2 );
void	AnglesSubtract( vec3_t v1, vec3_t v2, vec3_t v3 );

float AngleNormalize360 ( float angle );
float AngleNormalize180 ( float angle );
float AngleDelta ( float angle1, float angle2 );

qboolean PlaneFromPoints( vec4_t plane, const vec3_t a, const vec3_t b, const vec3_t c );
void ProjectPointOnPlane( vec3_t dst, const vec3_t p, const vec3_t normal );
void RotatePointAroundVector( vec3_t dst, const vec3_t dir, const vec3_t point, float degrees );
void RotateAroundDirection( matrix3_t axis, float yaw );
void MakeNormalVectors( const vec3_t forward, vec3_t right, vec3_t up );
// perpendicular vector could be replaced by this

//int	PlaneTypeForNormal (vec3_t normal);

void MatrixMultiply(float in1[3][3], float in2[3][3], float out[3][3]);
void AngleVectors( const vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
void PerpendicularVector( vec3_t dst, const vec3_t src );
void NormalToLatLong( const vec3_t normal, byte bytes[2] ); //rwwRMG - added

//=============================================

int Com_Clampi( int min, int max, int value ); //rwwRMG - added
float Com_Clamp( float min, float max, float value );
int Com_AbsClampi( int min, int max, int value );
float Com_AbsClamp( float min, float max, float value );

char	*COM_SkipPath( char *pathname );
const char	*COM_GetExtension( const char *name );
void	COM_StripExtension( const char *in, char *out, int destsize );
qboolean COM_CompareExtension(const char *in, const char *ext);
void	COM_DefaultExtension( char *path, int maxSize, const char *extension );

void	COM_BeginParseSession( const char *name );
int		COM_GetCurrentParseLine( void );
const char	*SkipWhitespace( const char *data, qboolean *hasNewLines );
char	*COM_Parse( const char **data_p );
char	*COM_ParseExt( const char **data_p, qboolean allowLineBreak );
int		COM_Compress( char *data_p );
void	COM_ParseError( char *format, ... );
void	COM_ParseWarning( char *format, ... );
qboolean COM_ParseString( const char **data, const char **s );
qboolean COM_ParseInt( const char **data, int *i );
qboolean COM_ParseFloat( const char **data, float *f );
qboolean COM_ParseVec4( const char **buffer, vec4_t *c);
//int		COM_ParseInfos( char *buf, int max, char infos[][MAX_INFO_STRING] );

#define MAX_TOKENLENGTH		1024

#ifndef TT_STRING
//token types
#define TT_STRING					1			// string
#define TT_LITERAL					2			// literal
#define TT_NUMBER					3			// number
#define TT_NAME						4			// name
#define TT_PUNCTUATION				5			// punctuation
#endif

typedef struct pc_token_s
{
	int type;
	int subtype;
	int intvalue;
	float floatvalue;
	char string[MAX_TOKENLENGTH];
} pc_token_t;

// data is an in/out parm, returns a parsed out token

void	COM_MatchToken( const char**buf_p, char *match );

void SkipBracedSection (const char **program);
void SkipRestOfLine ( const char **data );

void Parse1DMatrix (const char **buf_p, int x, float *m);
void Parse2DMatrix (const char **buf_p, int y, int x, float *m);
void Parse3DMatrix (const char **buf_p, int z, int y, int x, float *m);
int Com_HexStrToInt( const char *str );

int	QDECL Com_sprintf (char *dest, int size, const char *fmt, ...);

char *Com_SkipTokens( char *s, int numTokens, char *sep );
char *Com_SkipCharset( char *s, char *sep );

void Com_RandomBytes( byte *string, int len );

// mode parm for FS_FOpenFile
typedef enum {
	FS_READ,
	FS_WRITE,
	FS_APPEND,
	FS_APPEND_SYNC
} fsMode_t;

typedef enum {
	FS_SEEK_CUR,
	FS_SEEK_END,
	FS_SEEK_SET
} fsOrigin_t;

//=============================================

int Q_isprint( int c );
int Q_islower( int c );
int Q_isupper( int c );
int Q_isalpha( int c );
qboolean Q_isanumber( const char *s );
qboolean Q_isintegral( float f );

// portable case insensitive compare
int		Q_stricmp (const char *s1, const char *s2);
int		Q_strncmp (const char *s1, const char *s2, int n);
int		Q_stricmpn (const char *s1, const char *s2, int n);
char	*Q_strlwr( char *s1 );
char	*Q_strupr( char *s1 );
char	*Q_strrchr( const char* string, int c );

// buffer size safe library replacements
void	Q_strncpyz( char *dest, const char *src, int destsize );
void	Q_strcat( char *dest, int size, const char *src );

const char *Q_stristr( const char *s, const char *find);

// strlen that discounts Quake color sequences
int Q_PrintStrlen( const char *string );
// removes color sequences from string
char *Q_CleanStr( char *string );
void Q_StripColor(char *text);
void Q_strstrip( char *string, const char *strip, const char *repl );
const char *Q_strchrs( const char *string, const char *search );

//=============================================

// 64-bit integers for global rankings interface
// implemented as a struct for qvm compatibility
typedef struct qint64_s {
	byte	b0;
	byte	b1;
	byte	b2;
	byte	b3;
	byte	b4;
	byte	b5;
	byte	b6;
	byte	b7;
} qint64;

//=============================================
/*
short	BigShort(short l);
short	LittleShort(short l);
int		BigLong (int l);
int		LittleLong (int l);
qint64  BigLong64 (qint64 l);
qint64  LittleLong64 (qint64 l);
float	BigFloat (const float *l);
float	LittleFloat (const float *l);

void	Swap_Init (void);
*/

int FloatAsInt( float f );

char	* QDECL va(const char *format, ...);

#define TRUNCATE_LENGTH	64
void Com_TruncateLongString( char *buffer, const char *s );

//=============================================

//
// key / value info strings
//
char *Info_ValueForKey( const char *s, const char *key );
void Info_RemoveKey( char *s, const char *key );
void Info_RemoveKey_Big( char *s, const char *key );
void Info_SetValueForKey( char *s, const char *key, const char *value );
void Info_SetValueForKey_Big( char *s, const char *key, const char *value );
qboolean Info_Validate( const char *s );
qboolean Info_NextPair( const char **s, char *key, char *value );

// this is only here so the functions in q_shared.c and bg_*.c can link
//#if defined( _GAME ) || defined( _CGAME ) || defined( _UI )
//	void (*Com_Error)( int code, const char *fmt, ... );
//	void (*Com_Printf)( const char *msg, ... );
//#else
//	void QDECL Com_Error( int code, const char *fmt, ... );
//	void QDECL Com_Printf( const char *msg, ... );
//#endif

#if defined( _CGAME )
extern void QDECL CG_Error(int level, const char *error, ...);
extern void QDECL CG_Printf(const char *msg, ...);
#define Com_Error CG_Error
#define Com_Printf CG_Printf
#elif defined( _GAME )
extern void QDECL G_Error(int level, const char *error, ...);
extern void QDECL G_Printf(const char *msg, ...);
#define Com_Error G_Error
#define Com_Printf G_Printf
#elif defined( _UI )
extern void QDECL UI_Error( int level, const char *error, ... );
extern void QDECL UI_Printf(const char *msg, ...);
#define Com_Error UI_Error
#define Com_Printf UI_Printf
#else
	void QDECL Com_Error(int code, const char *fmt, ...);
	void QDECL Com_Printf(const char *msg, ...);
#endif

/*
==========================================================

CVARS (console variables)

Many variables can be used for cheating purposes, so when cheats is zero,
	force all unspecified variables to their cefault values.

==========================================================
*/

#define	CVAR_NONE			(0x00000000u)
#define	CVAR_ARCHIVE		(0x00000001u)	// set to cause it to be saved to configuration file. used for system variables,
											//	not for player specific configurations
#define	CVAR_USERINFO		(0x00000002u)	// sent to server on connect or change
#define	CVAR_SERVERINFO		(0x00000004u)	// sent in response to front end requests
#define	CVAR_SYSTEMINFO		(0x00000008u)	// these cvars will be duplicated on all clients
#define	CVAR_INIT			(0x00000010u)	// don't allow change from console at all, but can be set from the command line
#define	CVAR_LATCH			(0x00000020u)	// will only change when C code next does a Cvar_Get(), so it can't be changed
											//	without proper initialization. modified will be set, even though the value
											//	hasn't changed yet
#define	CVAR_ROM			(0x00000040u)	// display only, cannot be set by user at all (can be set by code)
#define	CVAR_USER_CREATED	(0x00000080u)	// created by a set command
#define	CVAR_TEMP			(0x00000100u)	// can be set even when cheats are disabled, but is not archived
#define CVAR_CHEAT			(0x00000200u)	// can not be changed if cheats are disabled
#define CVAR_NORESTART		(0x00000400u)	// do not clear when a cvar_restart is issued
#define CVAR_INTERNAL		(0x00000800u)	// cvar won't be displayed, ever (for passwords and such)
#define	CVAR_PARENTAL		(0x00001000u)	// lets cvar system know that parental stuff needs to be updated
#define CVAR_SERVER_CREATED	(0x00002000u)	// cvar was created by a server the client connected to.
#define CVAR_VM_CREATED		(0x00004000u)	// cvar was created exclusively in one of the VMs.
#define CVAR_PROTECTED		(0x00008000u)	// prevent modifying this var from VMs or the server
// These flags are only returned by the Cvar_Flags() function
#define CVAR_MODIFIED		(0x40000000u)	// Cvar was modified
#define CVAR_NONEXISTENT	(0x80000000u)	// Cvar doesn't exist.

enum CvarType {
	CvarType_Any,
	CvarType_Int,
	CvarType_Float,
	CvarType_Bool,
	CvarType_String
};

// nothing outside the Cvar_*() functions should modify these fields!
typedef struct cvar_s {
	char			*name;

	qboolean		displayInfoSet = qfalse;
	char			displayName[256] = { 0 };
	char			description[1024] = { 0 };

	char			*string;
	char			*resetString;		// cvar_restart will reset to this value
	char			*latchedString;		// for CVAR_LATCH vars
	uint32_t		flags;
	qboolean		modified;			// set each time the cvar is changed
	int				modificationCount;	// incremented each time the cvar is changed
	float			value;				// atof( string )
	int				integer;			// atoi( string )
	qboolean		validate;
	qboolean		integral;
	float			min, max;
	CvarType		typeinfo;
	float			dragspeed;			// used by imgui
	struct cvar_s	*next, *prev;
	struct cvar_s	*hashNext, *hashPrev;
	int				hashIndex;
} cvar_t;

#define	MAX_CVAR_VALUE_STRING	256

typedef int	cvarHandle_t;

// the modules that run in the virtual machine can't access the cvar_t directly,
// so they must ask for structured updates
typedef struct vmCvar_s {
	cvarHandle_t	handle;
	int			modificationCount;
	float		value;
	int			integer;
	char		string[MAX_CVAR_VALUE_STRING];
} vmCvar_t;

/*
==============================================================

COLLISION DETECTION

==============================================================
*/

#include "game/surfaceflags.h"			// shared with the q3map utility

// plane types are used to speed some tests
// 0-2 are axial planes
#define	PLANE_X			0
#define	PLANE_Y			1
#define	PLANE_Z			2
#define	PLANE_NON_AXIAL	3


/*
=================
PlaneTypeForNormal
=================
*/

#define PlaneTypeForNormal(x) (x[0] == 1.0 ? PLANE_X : (x[1] == 1.0 ? PLANE_Y : (x[2] == 1.0 ? PLANE_Z : PLANE_NON_AXIAL) ) )

// plane_t structure
// !!! if this is changed, it must be changed in asm code too !!!
typedef struct cplane_s {
	vec3_t	normal;
	float	dist;
	byte	type;			// for fast side tests: 0,1,2 = axial, 3 = nonaxial
	byte	signbits;		// signx + (signy<<1) + (signz<<2), used as lookup during collision
	byte	pad[2];
} cplane_t;
/*
Ghoul2 Insert Start
*/
typedef struct CollisionRecord_s {
	float		mDistance;
	int			mEntityNum;
	int			mModelIndex;
	int			mPolyIndex;
	int			mSurfaceIndex;
	vec3_t		mCollisionPosition;
	vec3_t		mCollisionNormal;
	int			mFlags;
	int			mMaterial;
	int			mLocation;
	float		mBarycentricI; // two barycentic coodinates for the hit point
	float		mBarycentricJ; // K = 1-I-J
} CollisionRecord_t;

#define MAX_G2_COLLISIONS 16

typedef CollisionRecord_t G2Trace_t[MAX_G2_COLLISIONS];	// map that describes all of the parts of ghoul2 models that got hit

/*
Ghoul2 Insert End
*/
// a trace is returned when a box is swept through the world
typedef struct trace_s {
	byte		allsolid;	// if true, plane is not valid
	byte		startsolid;	// if true, the initial point was in a solid area
	short		entityNum;	// entity the contacted sirface is a part of

	float		fraction;	// time completed, 1.0 = didn't hit anything
	vec3_t		endpos;		// final position
	cplane_t	plane;		// surface normal at impact, transformed to world space
	int			surfaceFlags;	// surface hit
	int			contents;	// contents on other side of surface hit
	int			materialType;
	char		*shaderName;

/*
Ghoul2 Insert Start
*/
	//rww - removed this for now, it's just wasting space in the trace structure.
//	CollisionRecord_t G2CollisionMap[MAX_G2_COLLISIONS];	// map that describes all of the parts of ghoul2 models that got hit
/*
Ghoul2 Insert End
*/
} trace_t;

// trace->entityNum can also be 0 to (MAX_GENTITIES-1)
// or ENTITYNUM_NONE, ENTITYNUM_WORLD


// markfragments are returned by CM_MarkFragments()
typedef struct markFragment_s {
	int		firstPoint;
	int		numPoints;
} markFragment_t;



typedef struct orientation_s {
	vec3_t		origin;
	matrix3_t	axis;
} orientation_t;

//=====================================================================


// in order from highest priority to lowest
// if none of the catchers are active, bound key strings will be executed
#define KEYCATCH_IMGUI			(1<<0)
#define KEYCATCH_CONSOLE		(1<<1)
#define	KEYCATCH_UI				(1<<2)
#define	KEYCATCH_MESSAGE		(1<<3)
#define	KEYCATCH_CGAME			(1<<4)


// sound channels
// channel 0 never willingly overrides
// other channels will allways override a playing sound on that channel
typedef enum {
	CHAN_AUTO,	//## %s !!"W:\game\base\!!sound\*.wav;*.mp3" # Auto-picks an empty channel to play sound on
	CHAN_LOCAL,	//## %s !!"W:\game\base\!!sound\*.wav;*.mp3" # menu sounds, etc
	CHAN_WEAPON,//## %s !!"W:\game\base\!!sound\*.wav;*.mp3"
	CHAN_WEAPONLOCAL,//## %s !!"W:\game\base\!!sound\*.wav;*.mp3"
	CHAN_VOICE, //## %s !!"W:\game\base\!!sound\voice\*.wav;*.mp3" # Voice sounds cause mouth animation
	CHAN_VOICE_ATTEN, //## %s !!"W:\game\base\!!sound\voice\*.wav;*.mp3" # Causes mouth animation but still use normal sound falloff
	CHAN_ITEM,  //## %s !!"W:\game\base\!!sound\*.wav;*.mp3"
	CHAN_BODY,	//## %s !!"W:\game\base\!!sound\*.wav;*.mp3"
	CHAN_AMBIENT,//## %s !!"W:\game\base\!!sound\*.wav;*.mp3" # added for ambient sounds
	CHAN_LOCAL_SOUND,	//## %s !!"W:\game\base\!!sound\*.wav;*.mp3" #chat messages, etc
	CHAN_ANNOUNCER,		//## %s !!"W:\game\base\!!sound\*.wav;*.mp3" #announcer voices, etc
	CHAN_LESS_ATTEN,	//## %s !!"W:\game\base\!!sound\*.wav;*.mp3" #attenuates similar to chan_voice, but uses empty channel auto-pick behaviour
	CHAN_MENU1,		//## %s !!"W:\game\base\!!sound\*.wav;*.mp3" #menu stuff, etc
	CHAN_VOICE_GLOBAL,  //## %s !!"W:\game\base\!!sound\voice\*.wav;*.mp3" # Causes mouth animation and is broadcast, like announcer
	CHAN_MUSIC,	//## %s !!"W:\game\base\!!sound\*.wav;*.mp3" #music played as a looping sound - added by BTO (VV)
} soundChannel_t;


/*
========================================================================

  ELEMENTS COMMUNICATED ACROSS THE NET

========================================================================
*/

#define	ANGLE2SHORT(x)	((int)((x)*65536/360) & 65535)
#define	SHORT2ANGLE(x)	((x)*(360.0/65536))

#define	SNAPFLAG_RATE_DELAYED	1
#define	SNAPFLAG_NOT_ACTIVE		2	// snapshot used during connection and for zombies
#define SNAPFLAG_SERVERCOUNT	4	// toggled every map_restart so transitions can be detected

//
// per-level limits
//
#ifdef __MMO__
//#define	MAX_CLIENTS			256		// absolute limit
#define	MAX_CLIENTS			128		// absolute limit - UQ1: Reducing to 128 for now...
//#define	MAX_CLIENTS			512
#else //!__MMO__
#define	MAX_CLIENTS			32		// absolute limit
#endif //__MMO__
#define MAX_RADAR_ENTITIES	MAX_GENTITIES
#define MAX_TERRAINS		1//32 //rwwRMG: inserted
#define MAX_LOCATIONS		64

#ifdef __MMO__
//#define	GENTITYNUM_BITS	11		// don't need to send any more
//#define	MAX_GENTITIES	(1<<GENTITYNUM_BITS)

//#define	GENTITYNUM_BITS	16		// don't need to send any more
#define	GENTITYNUM_BITS	11		// don't need to send any more - UQ1: 2^11 = 2048
#define		MAX_GENTITIES	(2048-1)
#else //!__MMO__
#define	GENTITYNUM_BITS	10		// don't need to send any more
#define	MAX_GENTITIES	(1<<GENTITYNUM_BITS)
#endif //__MMO__

//I am reverting. I guess. For now.
/*
#define	GENTITYNUM_BITS		11
							//rww - I am raising this 1 bit. SP actually has room for 1024 ents - none - world - 1 client.
							//Which means 1021 useable entities. However we have 32 clients.. so if we keep our limit
							//at 1024 we are not going to be able to load any SP levels at the edge of the ent limit.
#define		MAX_GENTITIES	(1024+(MAX_CLIENTS-1))
							//rww - we do have enough room to send over 2048 ents now. However, I cannot live with the guilt of
							//actually increasing the entity limit to 2048 (as it would slow down countless things, and
							//there are tons of ent list traversals all over the place). So I am merely going to give enough
							//to compensate for our larger maxclients.
*/

// entitynums are communicated with GENTITY_BITS, so any reserved
// values thatare going to be communcated over the net need to
// also be in this range
#define	ENTITYNUM_NONE		(MAX_GENTITIES-1)
#define	ENTITYNUM_WORLD		(MAX_GENTITIES-2)
#define	ENTITYNUM_MAX_NORMAL	(MAX_GENTITIES-2)


// these are also in be_aas_def.h - argh (rjr)
#ifdef __MMO__
#define	MAX_MODELS			1024	// these are sent over the net as -12 bits
#define	MAX_SOUNDS			1024	// so they cannot be blindly increased
#else //!__MMO__
#define	MAX_MODELS			512		// these are sent over the net as -12 bits
#define	MAX_SOUNDS			256		// so they cannot be blindly increased
#endif //__MMO__
#define MAX_ICONS			64		// max registered icons you can have per map
#define MAX_FX				64		// max effects strings, I'm hoping that 64 will be plenty

#define MAX_SUB_BSP			32 //rwwRMG - added

/*
Ghoul2 Insert Start
*/
#define	MAX_G2BONES		64		//rww - changed from MAX_CHARSKINS to MAX_G2BONES. value still equal.
/*
Ghoul2 Insert End
*/

#define MAX_AMBIENT_SETS		256 //rww - ambient soundsets must be sent over in config strings.

#ifdef __MMO__
//#define	MAX_CONFIGSTRINGS	5000 //this is getting pretty high. Try not to raise it anymore than it already is.
//#define	MAX_CONFIGSTRINGS	3500 //this is getting pretty high. Try not to raise it anymore than it already is.


//
// UQ1: Let's count them here and use the real maximum... Might save some bandwidth and/or corruption...
// This will need to continue to match bg_local.h's  CS_ values...
//

#define CCS_AMBIENT_SET			37
#define CCS_SIEGE_STATE			(CCS_AMBIENT_SET+MAX_AMBIENT_SETS)
#define CCS_SIEGE_OBJECTIVES	(CCS_SIEGE_STATE+1)
#define CCS_SIEGE_TIMEOVERRIDE	(CCS_SIEGE_OBJECTIVES+1)
#define CCS_SIEGE_WINTEAM		(CCS_SIEGE_TIMEOVERRIDE+1)
#define CCS_SIEGE_ICONS			(CCS_SIEGE_WINTEAM+1)
#define	CCS_MODELS				(CCS_SIEGE_ICONS+1)
#define	CCS_SKYBOXORG			(CCS_MODELS+MAX_MODELS)		//rww - skybox info
#define	CCS_SOUNDS				(CCS_SKYBOXORG+1)
#define CCS_ICONS				(CCS_SOUNDS+MAX_SOUNDS)
#define	CCS_PLAYERS				(CCS_ICONS+MAX_ICONS)
#define CCS_G2BONES				(CCS_PLAYERS+MAX_CLIENTS)
#define CCS_LOCATIONS			(CCS_G2BONES+MAX_G2BONES)
#define CCS_PARTICLES			(CCS_LOCATIONS+MAX_LOCATIONS)
#define CCS_EFFECTS				(CCS_PARTICLES+MAX_LOCATIONS)
#define	CCS_LIGHT_STYLES		(CCS_EFFECTS+MAX_FX)
#define CCS_TERRAINS			(CCS_LIGHT_STYLES+(MAX_LIGHT_STYLES*3))
#define CCS_BSP_MODELS			(CCS_TERRAINS+MAX_TERRAINS)
#define CCS_MAX					(CCS_BSP_MODELS+MAX_SUB_BSP)

#define	MAX_CONFIGSTRINGS	CCS_MAX+1 // UQ1: Set to the actual real max value...

#else //!__MMO__
#define	MAX_CONFIGSTRINGS	1700 //this is getting pretty high. Try not to raise it anymore than it already is.
#endif //__MMO__

// these are the only configstrings that the system reserves, all the
// other ones are strictly for servergame to clientgame communication
#define	CS_SERVERINFO		0		// an info string with all the serverinfo cvars
#define	CS_SYSTEMINFO		1		// an info string for server system to client system configuration (timescale, etc)

#define	RESERVED_CONFIGSTRINGS	2	// game can't modify below this, only the system can

#ifdef __MMO__
//#define	MAX_GAMESTATE_CHARS	256000
#define	MAX_GAMESTATE_CHARS	64000
//#define	MAX_GAMESTATE_CHARS	32000
#else //!__MMO__
#define	MAX_GAMESTATE_CHARS	16000
#endif //__MMO__

typedef struct gameState_s {
	int			stringOffsets[MAX_CONFIGSTRINGS];
	char		stringData[MAX_GAMESTATE_CHARS];
	int			dataCount;
} gameState_t;

//=========================================================

// all the different tracking "channels"
typedef enum {
	TRACK_CHANNEL_NONE = 50,
	TRACK_CHANNEL_1,
	TRACK_CHANNEL_2, // force speed
	TRACK_CHANNEL_3, // force rage
	TRACK_CHANNEL_4,
	TRACK_CHANNEL_5, // force sight
	NUM_TRACK_CHANNELS
} trackchan_t;

// UQ1: 32 new flags for us to use... For whatever we need...
#define	EXF_GENDER_MALE			(1<<0)
#define	EXF_GENDER_DROID		(1<<1)
#define	EXF_GENDER_FEMALE		(1<<2)
#define	EXF_UNUSED3				(1<<3)
#define	EXF_UNUSED4				(1<<4)
#define	EXF_UNUSED5				(1<<5)
#define	EXF_UNUSED6				(1<<6)
#define	EXF_UNUSED7				(1<<7)
#define	EXF_UNUSED8				(1<<8)
#define	EXF_UNUSED9				(1<<9)
#define	EXF_UNUSED10			(1<<10)
#define	EXF_UNUSED11			(1<<11)
#define	EXF_UNUSED12			(1<<12)
#define	EXF_UNUSED13			(1<<13)
#define	EXF_UNUSED14			(1<<14)
#define	EXF_UNUSED15			(1<<15)
#define	EXF_UNUSED16			(1<<16)
#define	EXF_UNUSED17			(1<<17)
#define	EXF_UNUSED18			(1<<18)
#define	EXF_UNUSED19			(1<<19)
#define	EXF_UNUSED20			(1<<20)
#define	EXF_UNUSED21			(1<<21)
#define	EXF_UNUSED22			(1<<22)
#define	EXF_UNUSED23			(1<<23)
#define	EXF_UNUSED24			(1<<24)
#define	EXF_UNUSED25			(1<<25)
#define	EXF_UNUSED26			(1<<26)
#define	EXF_UNUSED27			(1<<27)
#define	EXF_UNUSED28			(1<<28)
#define	EXF_UNUSED29			(1<<29)
#define	EXF_UNUSED30			(1<<30)
#define	EXF_UNUSED31			(1<<31)

#define TRACK_CHANNEL_MAX (NUM_TRACK_CHANNELS-50)

typedef struct forcedata_s {
	int			forcePowerDebounce[NUM_FORCE_POWERS];	//for effects that must have an interval
	int			forcePowersKnown;
	int			forcePowersActive;
	int			forcePowerSelected;
	int			forceButtonNeedRelease;
	int			forcePowerDuration[NUM_FORCE_POWERS];
	int			forcePower;
	int			forcePowerMax;
	int			forcePowerRegenDebounceTime;
	int			forcePowerLevel[NUM_FORCE_POWERS];		//so we know the max forceJump power you have
	int			forcePowerBaseLevel[NUM_FORCE_POWERS];
	int			forceUsingAdded;
	float		forceJumpZStart;					//So when you land, you don't get hurt as much
	float		forceJumpCharge;					//you're current forceJump charge-up level, increases the longer you hold the force jump button down
	int			forceJumpSound;
	int			forceJumpAddTime;
	int			forceGripEntityNum;					//what entity I'm gripping
	int			forceGripDamageDebounceTime;		//debounce for grip damage
	float		forceGripBeingGripped;				//if > level.time then client is in someone's grip
	int			forceGripCripple;					//if != 0 then make it so this client can't move quickly (he's being gripped)
	int			forceGripUseTime;					//can't use if > level.time
	float		forceGripSoundTime;
	float		forceGripStarted;					//level.time when the grip was activated
	int			forceHealTime;
	int			forceHealAmount;

	//This hurts me somewhat to do, but there's no other real way to allow completely "dynamic" mindtricking.
	int			forceMindtrickTargetIndex; //0-15
	int			forceMindtrickTargetIndex2; //16-32
	int			forceMindtrickTargetIndex3; //33-48
	int			forceMindtrickTargetIndex4; //49-64

	int			forceRageRecoveryTime;
	int			forceDrainEntNum;
	float		forceDrainTime;

	int			forceDoInit;

	int			forceSide;
	int			forceRank;

	int			forceDeactivateAll;

	int			killSoundEntIndex[TRACK_CHANNEL_MAX]; //this goes here so it doesn't get wiped over respawn

	qboolean	sentryDeployed;

	int			saberAnimLevelBase;//sigh...
	int			saberAnimLevel;
	int			saberDrawAnimLevel;

	int			suicides;

	int			privateDuelTime;
} forcedata_t;


typedef enum {
	SENTRY_NOROOM = 1,
	SENTRY_ALREADYPLACED,
	SHIELD_NOROOM,
	SEEKER_ALREADYDEPLOYED
} itemUseFail_t;

// bit field limits
#ifdef __MMO__
#define	MAX_STATS				16
#define	MAX_PERSISTANT			16
#define	MAX_POWERUPS			16
#else //!
#define	MAX_STATS				16
#define	MAX_PERSISTANT			16
#define	MAX_POWERUPS			16
#endif //__MMO__

#define	MAX_PS_EVENTS			2

#define PS_PMOVEFRAMECOUNTBITS	6

#define FORCE_LIGHTSIDE			1
#define FORCE_DARKSIDE			2

#define MAX_FORCE_RANK			7

#define FALL_FADE_TIME			3000

//#define _ONEBIT_COMBO
//Crazy optimization attempt to take all those 1 bit values and shove them into a single
//send. May help us not have to send so many 1/0 bits to acknowledge modified values. -rww

#define _OPTIMIZED_VEHICLE_NETWORKING
//Instead of sending 2 full playerStates for the pilot and the vehicle, send a smaller,
//specialized pilot playerState and vehicle playerState.  Also removes some vehicle
//fields from the normal playerState -mcg

// playerState_t is the information needed by both the client and server
// to predict player motion and actions
// nothing outside of pmove should modify these, or some degree of prediction error
// will occur

// you can't add anything to this without modifying the code in msg.c

// playerState_t is a full superset of entityState_t as it is used by players,
// so if a playerState_t is transmitted, the entityState_t can be fully derived
// from it.
typedef struct playerState_s {
	int			commandTime;	// cmd->serverTime of last executed command
	int			pm_type;
	int			bobCycle;		// for view bobbing and footstep generation
	int			pm_flags;		// ducked, jump_held, etc
	int			pm_time;

	vec3_t		origin;
	vec3_t		velocity;

	vec3_t		moveDir; //NOT sent over the net - nor should it be.

	int			weaponTime;
	int			weaponChargeTime;
	int			weaponChargeSubtractTime;
	int			gravity;
	float		speed;
	int			basespeed; //used in prediction to know base server g_speed value when modifying speed between updates
	int			delta_angles[3];	// add to command angles to get view direction
									// changed by spawns, rotating objects, and teleporters

	int			slopeRecalcTime; //this is NOT sent across the net and is maintained seperately on game and cgame in pmove code.

	int			useTime;

	int			groundEntityNum;// ENTITYNUM_NONE = in air

	int			legsTimer;		// don't change low priority animations until this runs out
	int			legsAnim;

	int			torsoTimer;		// don't change low priority animations until this runs out
	int			torsoAnim;

	qboolean	legsFlip; //set to opposite when the same anim needs restarting, sent over in only 1 bit. Cleaner and makes porting easier than having that god forsaken ANIM_TOGGLEBIT.
	qboolean	torsoFlip;

	int			movementDir;	// a number 0 to 7 that represents the reletive angle
								// of movement to the view angle (axial and diagonals)
								// when at rest, the value will remain unchanged
								// used to twist the legs during strafing

	int			eFlags;			// copied to entityState_t->eFlags
	int			eFlags2;		// copied to entityState_t->eFlags2, EF2_??? used much less frequently

	int			eventSequence;	// pmove generated events
	int			events[MAX_PS_EVENTS];
	int			eventParms[MAX_PS_EVENTS];

	int			externalEvent;	// events set on player from another source
	int			externalEventParm;
	int			externalEventTime;

	int			clientNum;		// ranges from 0 to MAX_CLIENTS-1
	int			weapon;			// copied to entityState_t->weapon
	int			weaponstate;

	vec3_t		viewangles;		// for fixed views
	int			viewheight;

	// damage feedback
	int			damageEvent;	// when it changes, latch the other parms
	int			damageYaw;
	int			damagePitch;
	int			damageCount;
	int			damageType;

	int			painTime;		// used for both game and client side to process the pain twitch - NOT sent across the network
	int			painDirection;	// NOT sent across the network
	float		yawAngle;		// NOT sent across the network
	qboolean	yawing;			// NOT sent across the network
	float		pitchAngle;		// NOT sent across the network
	qboolean	pitching;		// NOT sent across the network

	int			stats[MAX_STATS];
	int			persistant[MAX_PERSISTANT];	// stats that aren't cleared on death
	int			powerups[MAX_POWERUPS];	// level.time that the powerup runs out

	int			generic1;
	int			loopSound;
	int			jumppad_ent;	// jumppad entity hit this frame

	// not communicated over the net at all
	int			ping;			// server to game info for scoreboard
	int			pmove_framecount;	// FIXME: don't transmit over the network
	int			jumppad_frame;
	int			entityEventSequence;

	int			lastOnGround;	//last time you were on the ground

	qboolean	saberInFlight;

	int			saberMove;
	int			saberBlocking;
	int			saberBlocked;

	int			saberLockTime;
	int			saberLockEnemy;
	int			saberLockFrame; //since we don't actually have the ability to get the current anim frame
	int			saberLockHits; //every x number of buttons hits, allow one push forward in a saber lock (server only)
	int			saberLockHitCheckTime; //so we don't allow more than 1 push per server frame
	int			saberLockHitIncrementTime; //so we don't add a hit per attack button press more than once per server frame
	qboolean	saberLockAdvance; //do an advance (sent across net as 1 bit)

	int			saberEntityNum;
	float		saberEntityDist;
	int			saberEntityState;
	int			saberThrowDelay;
	qboolean	saberCanThrow;
	int			saberDidThrowTime;
	int			saberDamageDebounceTime;
	int			saberHitWallSoundDebounceTime;
	int			saberEventFlags;

	int			rocketLockIndex;
	float		rocketLastValidTime;
	float		rocketLockTime;
	float		rocketTargetTime;

	int			emplacedIndex;
	float		emplacedTime;

	qboolean	isJediMaster;
	qboolean	forceRestricted;
	qboolean	trueJedi;
	qboolean	trueNonJedi;
	int			saberIndex;

	int			genericEnemyIndex;
	float		droneFireTime;
	float		droneExistTime;

	int			activeForcePass;

	qboolean	hasDetPackPlanted; //better than taking up an eFlag isn't it?

	float		holocronsCarried[NUM_FORCE_POWERS];
	int			holocronCantTouch;
	float		holocronCantTouchTime; //for keeping track of the last holocron that just popped out of me (if any)
	int			holocronBits;

	int			electrifyTime;

	int			saberAttackSequence;
	int			saberIdleWound;
	int			saberAttackWound;
	int			saberBlockTime;

	int			otherKiller;
	int			otherKillerTime;
	int			otherKillerDebounceTime;

	forcedata_t	fd;
	qboolean	forceJumpFlip;
	int			forceHandExtend;
	int			forceHandExtendTime;

	int			forceRageDrainTime;

	int			forceDodgeAnim;
	qboolean	quickerGetup;

	int			groundTime;		// time when first left ground

	int			footstepTime;

	int			otherSoundTime;
	float		otherSoundLen;

	int			forceGripMoveInterval;
	int			forceGripChangeMovetype;

	int			forceKickFlip;

	int			duelIndex;
	int			duelTime;
	qboolean	duelInProgress;

	int			saberAttackChainCount;

	int			saberHolstered;

	int			forceAllowDeactivateTime;

	// zoom key
	int			scopeType;		// 0 - not zoomed, scopeTypes_t;
	int			zoomTime;
	qboolean	zoomLocked;
	float		zoomFov;
	int			zoomLockTime;

	int			fallingToDeath;

	int			useDelay;

	qboolean	inAirAnim;

	vec3_t		lastHitLoc;

	int			heldByClient; //can only be a client index - this client should be holding onto my arm using IK stuff.

	int			ragAttach; //attach to ent while ragging

	int			iModelScale;

	int			brokenLimbs;

	//for looking at an entity's origin (NPCs and players)
	qboolean	hasLookTarget;
	int			lookTarget;

	int			customRGBA[4];

	int			standheight;
	int			crouchheight;

	//If non-0, this is the index of the vehicle a player/NPC is riding.
	int			m_iVehicleNum;

	//lovely hack for keeping vehicle orientation in sync with prediction
	vec3_t		vehOrientation;
	qboolean	vehBoarding;
	int			vehSurfaces;

	//vehicle turnaround stuff (need this in ps so it doesn't jerk too much in prediction)
	int			vehTurnaroundIndex;
	int			vehTurnaroundTime;

	//vehicle has weapons linked
	qboolean	vehWeaponsLinked;

	//when hyperspacing, you just go forward really fast for HYPERSPACE_TIME
	int			hyperSpaceTime;
	vec3_t		hyperSpaceAngles;

	//hacking when > time
	int			hackingTime;
	//actual hack amount - only for the proper percentage display when
	//drawing progress bar (is there a less bandwidth-eating way to do
	//this without a lot of hassle?)
	int			hackingBaseTime;

	//keeps track of jetpack fuel
	int			jetpackFuel;

	//keeps track of cloak fuel
	int			cloakFuel;

	// UQ1: Added - to display damage stats on client...
	qboolean	damageCrit;
	int			damageValue;

	unsigned char   shotsRemaining;

	int 			damageTypeFlags;
	int 			freezeTorsoAnim;
	int 			freezeLegsAnim;

	//Keeps Trak of Block Point
	
	signed short	forcePower;
	int				playerClass;

	int				primaryWeapon;
	int				secondaryWeapon;
	int				temporaryWeapon;

	int				eventIndex;

	// UQ1: Added - Extra flags...
	int			extra_flags;

	int			healFxTime;

	//index values for each type of sound, gets the folder the sounds
	//are in. I wish there were a better way to do this,
	int		csSounds_Std;
	int		csSounds_Combat;
	int		csSounds_Extra;
	int		csSounds_Jedi;

	int			nextStyleSwitch;

	//rww - spare values specifically for use by mod authors.
	//See psf_overrides.txt if you want to increase the send
	//amount of any of these above 1 bit.
	int			userInt1;
	int			userInt2;
	int			userInt3;
	float		userFloat1;
	float		userFloat2;
	float		userFloat3;
	vec3_t		userVec1;
	vec3_t		userVec2;

#ifdef _ONEBIT_COMBO
	int			deltaOneBits;
	int			deltaNumBits;
#endif

} playerState_t;

typedef struct siegePers_s
{
	qboolean	beatingTime;
	int			lastTeam;
	int			lastTime;
} siegePers_t;

//====================================================================


//
// usercmd_t->button bits, many of which are generated by the client system,
// so they aren't game/cgame only definitions
//
#define	BUTTON_ATTACK			1
#define	BUTTON_TALK				2			// displays talk balloon and disables actions
#define	BUTTON_USE_HOLDABLE		4
#define	BUTTON_GESTURE			8
#define	BUTTON_WALKING			16			// walking can't just be infered from MOVE_RUN
										// because a key pressed late in the frame will
										// only generate a small move value for that frame
										// walking will use different animations and
										// won't generate footsteps
#define	BUTTON_USE				32			// the ol' use key returns!
#define BUTTON_FORCEGRIP		64			//
#define BUTTON_ALT_ATTACK		128

#define	BUTTON_ANY				256			// any key whatsoever

#define BUTTON_FORCEPOWER		512			// use the "active" force power

#define BUTTON_FORCE_LIGHTNING	1024

#define BUTTON_FORCE_DRAIN		2048

#define BUTTON_SABERTHROW       4096        //+button12			//+button12 //Also a small force use button for repulse
#define BUTTON_SPECIALBUTTON1   8192        //+button13			//+button13 Slap Button
#define BUTTON_SPECIALBUTTON2	16384		//+button14			//+button14 kick button

// Here's an interesting bit.  The bots in TA used buttons to do additional gestures.
// I ripped them out because I didn't want too many buttons given the fact that I was already adding some for JK2.
// We can always add some back in if we want though.
/*
#define BUTTON_AFFIRMATIVE	32
#define	BUTTON_NEGATIVE		64

#define BUTTON_GETFLAG		128
#define BUTTON_GUARDBASE	256
#define BUTTON_PATROL		512
#define BUTTON_FOLLOWME		1024
*/

#define	MOVE_RUN			120			// if forwardmove or rightmove are >= MOVE_RUN,
										// then BUTTON_WALKING should be set

typedef enum
{
	GENCMD_SABERSWITCH = 1,
	GENCMD_ENGAGE_DUEL,
	GENCMD_FORCE_HEAL,
	GENCMD_FORCE_SPEED,
	GENCMD_FORCE_THROW,
	GENCMD_FORCE_PULL,
	GENCMD_FORCE_DISTRACT,
	GENCMD_FORCE_RAGE,
	GENCMD_FORCE_PROTECT,
	GENCMD_FORCE_ABSORB,
	GENCMD_FORCE_HEALOTHER,
	GENCMD_FORCE_FORCEPOWEROTHER,
	GENCMD_FORCE_SEEING,
	GENCMD_USE_SEEKER,
	GENCMD_USE_FIELD,
	GENCMD_USE_BACTA,
	GENCMD_USE_ELECTROBINOCULARS,
	GENCMD_ZOOM,
	GENCMD_USE_SENTRY,
	GENCMD_USE_JETPACK,
	GENCMD_USE_BACTABIG,
	GENCMD_USE_HEALTHDISP,
	GENCMD_USE_AMMODISP,
	GENCMD_USE_EWEB,
	GENCMD_USE_CLOAK,
	GENCMD_SABERATTACKCYCLE,
	GENCMD_TAUNT,
	GENCMD_BOW,
	GENCMD_MEDITATE,
	GENCMD_FLOURISH,
	GENCMD_GLOAT
} genCmds_t;

// usercmd_t is sent to the server each client frame
typedef struct usercmd_s {
	int				serverTime;
	int				angles[3];
	int 			buttons;
	byte			weapon;           // weapon
	byte			forcesel;
	byte			invensel;
	byte			generic_cmd;
	signed char	forwardmove, rightmove, upmove;
} usercmd_t;

//===================================================================

//rww - unsightly hack to allow us to make an FX call that takes a horrible amount of args
typedef struct addpolyArgStruct_s {
	vec3_t				p[4];
	vec2_t				ev[4];
	int					numVerts;
	vec3_t				vel;
	vec3_t				accel;
	float				alpha1;
	float				alpha2;
	float				alphaParm;
	vec3_t				rgb1;
	vec3_t				rgb2;
	float				rgbParm;
	vec3_t				rotationDelta;
	float				bounce;
	int					motionDelay;
	int					killTime;
	qhandle_t			shader;
	int					flags;
} addpolyArgStruct_t;

typedef struct addbezierArgStruct_s {
	vec3_t start;
	vec3_t end;
	vec3_t control1;
	vec3_t control1Vel;
	vec3_t control2;
	vec3_t control2Vel;
	float size1;
	float size2;
	float sizeParm;
	float alpha1;
	float alpha2;
	float alphaParm;
	vec3_t sRGB;
	vec3_t eRGB;
	float rgbParm;
	int killTime;
	qhandle_t shader;
	int flags;
} addbezierArgStruct_t;

typedef struct addspriteArgStruct_s
{
	vec3_t origin;
	vec3_t vel;
	vec3_t accel;
	float scale;
	float dscale;
	float sAlpha;
	float eAlpha;
	float rotation;
	float bounce;
	int life;
	qhandle_t shader;
	int flags;
} addspriteArgStruct_t;

typedef struct effectTrailVertStruct_s {
	vec3_t	origin;

	// very specifc case, we can modulate the color and the alpha
	vec3_t	rgb;
	vec3_t	destrgb;
	vec3_t	curRGB;

	float	alpha;
	float	destAlpha;
	float	curAlpha;

	// this is a very specific case thing...allow interpolating the st coords so we can map the texture
	//	properly as this segement progresses through it's life
	float	ST[2];
	float	destST[2];
	float	curST[2];
} effectTrailVertStruct_t;

typedef struct effectTrailArgStruct_s {
	effectTrailVertStruct_t		mVerts[4];
	qhandle_t					mShader;
	int							mSetFlags;
	int							mKillTime;
} effectTrailArgStruct_t;

typedef struct addElectricityArgStruct_s {
	vec3_t start;
	vec3_t end;
	float size1;
	float size2;
	float sizeParm;
	float alpha1;
	float alpha2;
	float alphaParm;
	vec3_t sRGB;
	vec3_t eRGB;
	float rgbParm;
	float chaos;
	int killTime;
	qhandle_t shader;
	int flags;
} addElectricityArgStruct_t;

// if entityState->solid == SOLID_BMODEL, modelindex is an inline model number
#define	SOLID_BMODEL	0xffffff

typedef enum {
	TR_STATIONARY,
	TR_INTERPOLATE,				// non-parametric, but interpolate between snapshots
	TR_LINEAR,
	TR_LINEAR_STOP,
	TR_NONLINEAR_STOP,
	TR_SINE,					// value = base + sin( time / duration ) * delta
	TR_GRAVITY
} trType_t;

typedef struct trajectory_s {
	trType_t	trType;
	int		trTime;
	int		trDuration;			// if non 0, trTime + trDuration = stop time
	vec3_t	trBase;
	vec3_t	trDelta;			// velocity, etc
} trajectory_t;

// entityState_t is the information conveyed from the server
// in an update message about entities that the client will
// need to render in some way
// Different eTypes may use the information in different ways
// The messages are delta compressed, so it doesn't really matter if
// the structure size is fairly large
typedef struct entityState_s {
	int		number;			// entity index
	int		eType;			// entityType_t
	int		eFlags;
	int		eFlags2;		// EF2_??? used much less frequently

	trajectory_t	pos;	// for calculating position
	trajectory_t	apos;	// for calculating angles

	int		time;
	int		time2;

	vec3_t	origin;
	vec3_t	origin2;

	vec3_t	angles;
	vec3_t	angles2;

	//rww - these were originally because we shared g2 info client and server side. Now they
	//just get used as generic values everywhere.
	int		bolt1;
	int		bolt2;

	//rww - this is necessary for determining player visibility during a jedi mindtrick
	int		trickedentindex; //0-15
	int		trickedentindex2; //16-32
	int		trickedentindex3; //33-48
	int		trickedentindex4; //49-64

	float	speed;

	int		fireflag;

	int		genericenemyindex;

	int		activeForcePass;

	int		emplacedOwner;

	int		otherEntityNum;	// shotgun sources, etc
	int		otherEntityNum2;

	int		groundEntityNum;	// ENTITYNUM_NONE = in air

	int		constantLight;	// r + (g<<8) + (b<<16) + (intensity<<24)
	int		loopSound;		// constantly loop this sound
	qboolean	loopIsSoundset; //qtrue if the loopSound index is actually a soundset index

	int		soundSetIndex;

	int		modelGhoul2;
	int		g2radius;
	int		modelindex;
	int		modelindex2;
	int		clientNum;		// 0 to (MAX_CLIENTS - 1), for players and corpses
	int		frame;

	qboolean	saberInFlight;
	int			saberEntityNum;
	int			saberMove;
	int			forcePowersActive;
	int			saberHolstered;//sent in only only 2 bits - should be 0, 1 or 2

	qboolean	isJediMaster;

	qboolean	isPortalEnt; //this needs to be seperate for all entities I guess, which is why I couldn't reuse another value.

	int		solid;			// for client side prediction, trap_linkentity sets this properly

	int		event;			// impulse events -- muzzle flashes, footsteps, etc
	int		eventParm;

	// so crosshair knows what it's looking at
	int			owner;
	int			teamowner;
	qboolean	shouldtarget;

	// for players
	int		powerups;		// bit flags
	int		weapon;			// determines weapon and flash model, etc
	int		legsAnim;
	int		torsoAnim;

	qboolean	legsFlip; //set to opposite when the same anim needs restarting, sent over in only 1 bit. Cleaner and makes porting easier than having that god forsaken ANIM_TOGGLEBIT.
	qboolean	torsoFlip;

	int		forceFrame;		//if non-zero, force the anim frame

	int		generic1;

	int		heldByClient; //can only be a client index - this client should be holding onto my arm using IK stuff.

	int		ragAttach; //attach to ent while ragging

	int		iModelScale; //rww - transfer a percentage of the normal scale in a single int instead of 3 x-y-z scale values

	int		brokenLimbs;

	int		boltToPlayer; //set to index of a real client+1 to bolt the ent to that client. Must be a real client, NOT an NPC.

	//for looking at an entity's origin (NPCs and players)
	qboolean	hasLookTarget;
	int			lookTarget;

	int			customRGBA[4];

	//I didn't want to do this, but I.. have no choice. However, we aren't setting this for all ents or anything,
	//only ones we want health knowledge about on cgame (like siege objective breakables) -rww
	int			health;
	int			maxhealth; //so I know how to draw the stupid health bar

	//int			Shield;
	//int			maxShield;	// Shieldbar -- UQ1: Stois, you can't add fields to entityState_t.
								// It has to remain at it's original exact size as the engine sends only that size of data.
								// We may be better off forgetting shields and just increasing HP.

	//NPC-SPECIFIC FIELDS
	//------------------------------------------------------------
	int		npcSaber1;
	int		npcSaber2;

	//index values for each type of sound, gets the folder the sounds
	//are in. I wish there were a better way to do this,
	int		csSounds_Std;
	int		csSounds_Combat;
	int		csSounds_Extra;
	int		csSounds_Jedi;

	int		surfacesOn; //a bitflag of corresponding surfaces from a lookup table. These surfaces will be forced on.
	int		surfacesOff; //same as above, but forced off instead.

	//Allow up to 4 PCJ lookup values to be stored here.
	//The resolve to configstrings which contain the name of the
	//desired bone.
	int		boneIndex1;
	int		boneIndex2;
	int		boneIndex3;
	int		boneIndex4;

	//packed with x, y, z orientations for bone angles
	int		boneOrient;

	//I.. feel bad for doing this, but NPCs really just need to
	//be able to control this sort of thing from the server sometimes.
	//At least it's at the end so this stuff is never going to get sent
	//over for anything that isn't an NPC.
	vec3_t	boneAngles1; //angles of boneIndex1
	vec3_t	boneAngles2; //angles of boneIndex2
	vec3_t	boneAngles3; //angles of boneIndex3
	vec3_t	boneAngles4; //angles of boneIndex4

	int		NPC_class; //we need to see what it is on the client for a few effects.

	//If non-0, this is the index of the vehicle a player/NPC is riding.
	int		m_iVehicleNum;

// UQ1: Added - to display damage stats on client...
	qboolean	damageCrit;
	int			damageValue;

	int 		damageTypeFlags;
	int 		freezeTorsoAnim;
	int 		freezeLegsAnim;

	int			playerClass;

	int			primaryWeapon;
	int			secondaryWeapon;
	int			temporaryWeapon;

	int			eventIndex;

	int			NPC_NAME_ID;

	// UQ1: Added - Extra flags...
	int			extra_flags;

	int			healFxTime;

	//rww - spare values specifically for use by mod authors.
	//See netf_overrides.txt if you want to increase the send
	//amount of any of these above 1 bit.
	int			userInt1;
	int			userInt2;
	int			userInt3;
	float		userFloat1;
	float		userFloat2;
	float		userFloat3;
	vec3_t		userVec1;
	vec3_t		userVec2;
} entityState_t;

typedef enum {
	CA_UNINITIALIZED,
	CA_DISCONNECTED, 	// not talking to a server
	CA_AUTHORIZING,		// not used any more, was checking cd key
	CA_CONNECTING,		// sending request packets to the server
	CA_CHALLENGING,		// sending challenge packets to the server
	CA_CONNECTED,		// netchan_t established, getting gamestate
	CA_LOADING,			// only during cgame initialization, never during main loop
	CA_PRIMED,			// got gamestate, waiting for first frame
	CA_ACTIVE,			// game views should be displayed
	CA_CINEMATIC		// playing a cinematic or a static pic, not connected to a server
} connstate_t;


#define Square(x) ((x)*(x))

// real time
//=============================================


typedef struct qtime_s {
	int tm_sec;     /* seconds after the minute - [0,59] */
	int tm_min;     /* minutes after the hour - [0,59] */
	int tm_hour;    /* hours since midnight - [0,23] */
	int tm_mday;    /* day of the month - [1,31] */
	int tm_mon;     /* months since January - [0,11] */
	int tm_year;    /* years since 1900 */
	int tm_wday;    /* days since Sunday - [0,6] */
	int tm_yday;    /* days since January 1 - [0,365] */
	int tm_isdst;   /* daylight savings time flag */
} qtime_t;


// server browser sources
#define AS_LOCAL			0
#define AS_GLOBAL			1
#define AS_FAVORITES		2

#define AS_MPLAYER			3 // (Obsolete)

// cinematic states
typedef enum {
	FMV_IDLE,
	FMV_PLAY,		// play
	FMV_EOF,		// all other conditions, i.e. stop/EOF/abort
	FMV_ID_BLT,
	FMV_ID_IDLE,
	FMV_LOOPED,
	FMV_ID_WAIT
} e_status;

#define	MAX_GLOBAL_SERVERS			2048
#define	MAX_OTHER_SERVERS			128
#define MAX_PINGREQUESTS			32
#define MAX_SERVERSTATUSREQUESTS	16

#define SAY_ALL		0
#define SAY_TEAM	1
#define SAY_TELL	2

#define QRAND_MAX 32768 // UQ1: added irand_big() for big numbers

void Rand_Init(int seed);
float flrand(float min, float max);
int irand(int min, int max);
int Q_irand(int value1, int value2);
uint32_t irand_big(uint32_t a, uint32_t b);
//[SaberSys]
float VectorDistances(vec3_t v1, vec3_t v2);
//[/SaberSys]

/*
Ghoul2 Insert Start
*/

typedef struct mdxaBone_s {
	float		matrix[3][4];
} mdxaBone_t;

// For ghoul2 axis use

typedef enum Eorientations
{
	ORIGIN = 0,
	POSITIVE_X,
	POSITIVE_Z,
	POSITIVE_Y,
	NEGATIVE_X,
	NEGATIVE_Z,
	NEGATIVE_Y
} orientations_t;
/*
Ghoul2 Insert End
*/

// define the new memory tags for the zone, used by all modules now
//
#define TAGDEF(blah) TAG_ ## blah
typedef enum {
	#include "qcommon/tags.h"
} memtag;
typedef unsigned memtag_t;

//rww - conveniently toggle "gore" code, for model decals and stuff.
#define _G2_GORE

typedef struct SSkinGoreData_s
{
	vec3_t			angles;
	vec3_t			position;
	int				currentTime;
	int				entNum;
	vec3_t			rayDirection;	// in world space
	vec3_t			hitLocation;	// in world space
	vec3_t			scale;
	float			SSize;			// size of splotch in the S texture direction in world units
	float			TSize;			// size of splotch in the T texture direction in world units
	float			theta;			// angle to rotate the splotch

	// growing stuff
	int				growDuration;			// time over which we want this to scale up, set to -1 for no scaling
	float			goreScaleStartFraction; // fraction of the final size at which we want the gore to initially appear

	qboolean		frontFaces;
	qboolean		backFaces;
	qboolean		baseModelOnly;
	int				lifeTime;				// effect expires after this amount of time
	int				fadeOutTime;			//specify the duration of fading, from the lifeTime (e.g. 3000 will start fading 3 seconds before removal and be faded entirely by removal)
	int				shrinkOutTime;			// unimplemented
	float			alphaModulate;			// unimplemented
	vec3_t			tint;					// unimplemented
	float			impactStrength;			// unimplemented

	int				shader; // shader handle

	int				myIndex; // used internally

	qboolean		fadeRGB; //specify fade method to modify RGB (by default, the alpha is set instead)
} SSkinGoreData;

/*
========================================================================

String ID Tables

========================================================================
*/
#define ENUM2STRING(arg)   { #arg, arg }
typedef struct stringID_table_s
{
	const char	*name;
	int		id;
} stringID_table_t;

int GetIDForString ( stringID_table_t *table, const char *string );
const char *GetStringForID( stringID_table_t *table, int id );


// stuff to help out during development process, force reloading/uncacheing of certain filetypes...
//
typedef enum
{
	eForceReload_NOTHING,
//	eForceReload_BSP,	// not used in MP codebase
	eForceReload_MODELS,
	eForceReload_ALL

} ForceReload_e;


enum {
	FONT_NONE,
	FONT_SMALL=1,
	FONT_MEDIUM,
	FONT_LARGE,
	FONT_SMALL2
};

void NET_AddrToString( char *out, size_t size, void *addr );
float Q_clamp(float min, float value, float max);
int Q_clampi(int min, int value, int max);

qboolean StringContainsWord(const char *haystack, const char *needle);
qboolean HaveWeapon( playerState_t *ps, int weapon );
qboolean WeaponIsPistol(int weapon);
qboolean WeaponIsSniper(int weapon);
qboolean WeaponIsSniperCharge(int weapon);
qboolean WeaponIsSniperNoCharge ( int weapon );
qboolean IsRollWithPistols(int weapon);
qboolean WeaponIsGrenade(int weapon);
qboolean WeaponIsRocketLauncher(int weapon);


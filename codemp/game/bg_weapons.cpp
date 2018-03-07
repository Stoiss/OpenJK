// Copyright (C) 2001-2002 Raven Software
//
// bg_weapons.c -- part of bg_pmove functionality

#include "qcommon/q_shared.h"
#include "bg_public.h"
#include "bg_local.h"

qboolean BG_HaveWeapon ( const playerState_t *ps, int weapon );

#if 0 // No longer needed...
// Muzzle point table...
vec3_t WP_MuzzlePoint[WP_NUM_WEAPONS] =
{//	Fwd,	right,	up.
	{0,		0,		 0	},	// WP_NONE,
	{0,		8,		 0	},	// WP_STUN_BATON,
	{0,	    8,		 0	},	// WP_MELEE,
	{8,		16,		 0	},	// WP_SABER,
	{30, 	2.5,	-1	},	// WP_BRYAR_PISTOL,
	{15, 	3.5,	-1	},	// WP_BRYAR_OLD,
	{30,	7,		-6	},	// WP_BLASTER,
	{20,	4,		-6	},	// WP_DISRUPTOR,
	{30,	7,		-6	},	// WP_BOWCASTER,
	{30,	6,	    -6	},	// WP_REPEATER,
	{12,	6,		-6	},	// WP_DEMP2,
	{12,	6,		-6	},	// WP_FLECHETTE,
	{12,	4,  	-10	},	// WP_CONCUSSION,
	//add new weapon here under the last new weapon.
	{12,	7,		-6	},	// WP_A280,
	{30,	9,      -6	},	// WP_DC15,
	{30,	9,  	-6	},	// WP_WESTARM5,
	{30,	4,		-6	},	// WP_T21,
	{30,	7,		-6	},	// WP_EE3,
	{30, 	3,		-1	},	// WP_DC_15S_CLONE_PISTOL,
	{30,	9,		-6	},	// WP_DLT_19,
	{30,	9,	    -6	},	// WP_DC_15A_RIFLE,
	{30, 	3.5,  	-1	},	// WP_WESTER_PISTOL,
	{30, 	3.5,  	-1	},	// WP_ELG_3A,
	{30, 	3,  	-1	},	// WP_S5_PISTOL,
	{12,	6,	    -6	},	// WP_Z6_BLASTER_CANON,
	{30,	7,		-6	},	// WP_HEAVY_BOWCASTER_SCOPE,
	{30, 	3.5,  	-1	},	// WP_WOOKIES_PISTOL,
	{30,	7,		-6	},	// WP_CLONE_BLASTER,
	{30,	9.5,  	-6	},	// WP_DC15_EXT,
	{30,	8,		-4	},  // WP_E60_ROCKET_LAUNCHER,
	{30,	8,		-4	},  // WP_CW_ROCKET_LAUNCHER,
	{30,    4,		-1	},	// WP_TESTGUN,
	{30,    3,		-1	},	// WP_DC_17_CLONE_PISTOL,
	{30,    4,		-1	},	// WP_SPOTING_BLASTER,
	{30,    6.5,	-1	},	// WP_A200_ACP_BATTLERIFLE,
	{30,    4,		-1	},	// WP_A200_ACP_PISTOL,
	{30,    6,		-1	},	// WP_ACP_ARRAYGUN,
	{30,	7,		-6	},	// WP_ACP_SNIPER_RIFLE,
	{12,	6,		-6	},	// WP_ARC_CASTER_IMPERIAL,
	{30,	7,		-6	},	// WP_BOWCASTER_CLASSIC,
	{30,	7,		-6	},	// WP_HEAVY_SCOPE_BOWCASTER,
	{30,	7.5,	-6	},	// WP_BRYAR_CARBINE,
	{30,	7.5,	-6	},	// WP_BRYAR_RIFLE,
	{30,	7.5,	-6	},	// WP_BRYAR_RIFLE_SCOPE,
	{30,	9,	    -6	},	// WP_PULSECANON,
	{30,	7,		-6	},	// WP_PROTON_CARBINE_RIFLE,
	{30, 	2.5,	-1	},	// WP_DH_17_PISTOL,
	//old weapons
	{30,	6,		-14	},	// WP_ROCKET_LAUNCHER,
	{12,	0,		-4	},	// WP_THERMAL,
	{12,	0,		-4	},	// WP_FRAG_GRENADE,
	{12,	0,		-4	},	// WP_FRAG_GRENADE_OLD,
	{12,	0,		-4	},	// WP_CYROBAN_GRENADE,
	{12,	0,		-10	},	// WP_TRIP_MINE,
	{12,	0,		-4	},	// WP_DET_PACK,

};
#endif

//ready for 2 handed pistols when ready for it. -- UQ1: Probably no longer needed - needs to be tested when we have 2 pistols...
vec3_t WP_FirstPistolMuzzle[WP_NUM_WEAPONS] = 
{//	Fwd,	right,	up.
	{ 12,	6,		0	},

};
vec3_t WP_SecondPistolMuzzle[WP_NUM_WEAPONS] = 
{//	Fwd,	right,	up.
	{ 12,  -6,		0	},

};

#define DEFAULT_DAMAGE				3
#define PISTOL_DMG					5//10
#define BLASTER_DAMAGE				10//20
#define ROCKET_DAMAGE				60
#define GRENADE_DAMAGE				70

#define DEFAULT_SPEED				2300
#define PISTOL_SPEED				1600
#define BLASTER_SPEED				DEFAULT_SPEED
#define GRENADE_SPEED				900

#define DEFAULT_ACCURACY			1.0f
#define PISTOL_ACCURACY				1.0f
#define BLASTER_ACCURACY			1.6f

#define DEFAULT_BURST_SHOT			0
#define BURST_SLOW_LOW				2
#define BURST_SHOT_MID				3
#define BURST_SHOT_HIGH				5

#define DEFAULT_BURST_DELAY			0
#define LOW_BURST_DELAY				175	
#define MID_BURST_DELAY				150
#define HIGH_BURST_DELAY			100

//#define	WFT_NORMAL					(firingType_t)0
#define	WFT_AUTO					(firingType_t)0
#define	WFT_SEMI					(firingType_t)1
#define	WFT_BURST					(firingType_t)2


//New clean weapon table NOTE* need to remeber to put the WP_NAME same place as you have added it in BG_weapon.h else it gets messed up in the weapon table
weaponData_t weaponData[WP_NUM_WEAPONS] = {
	// char	classname[32];							fireTime	altFireTime		firingType			burstFireDelay			  shotsPerBurst			dmg				dmgAlt				boltSpeed			accuracy				splashDmg		splashRadius	chargeSubTime	altChargeSubTime	altChargeSub
	{ "No Weapon",									0,			0,				WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	0,				0,					0,					0,						0,				0,				0,				0,					0,			},
	{ "Stun Baton",									400,		400,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	DEFAULT_DAMAGE,	DEFAULT_DAMAGE,		0,					0,						0,				0,				0,				0,					0,			},
	{ "Melee",										400,		400,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	5,				5,					0,					0,						0,				0,				0,				0,					0,			},
	{ "Light Saber",								100,		100,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	0,				0,					0,					0,						0,				0,				0,				0,					0,			},
	{ "Bryar Pistol",								800,		800,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	PISTOL_DMG,		PISTOL_DMG,			PISTOL_SPEED,		PISTOL_ACCURACY,		0,				0,				0,				0,					0,			},
	{ "Old Bryar Pistol",							600,		400,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	PISTOL_DMG,		PISTOL_DMG,			PISTOL_SPEED,		PISTOL_ACCURACY,		0,				0,				0,				200,				1,			},
	{ "E-11 Blaster Rifle",							350,		275,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	BLASTER_DAMAGE,	BLASTER_DAMAGE,		BLASTER_SPEED,		BLASTER_ACCURACY,		0,				0,				0,				200,				3,			},
	{ "Tenloss Disruptor Rifle",					600,		1300,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	30,				50,																0,				0,				0,				0,					0,			},
	{ "Modified Wookie Crossbow",					800,		750,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	BLASTER_DAMAGE, BLASTER_DAMAGE,		BLASTER_SPEED,		BLASTER_ACCURACY,		0,				0,				400,			0,					0,			},
	{ "Imperial Heavy Repeater",					250,		800,			WFT_BURST,			LOW_BURST_DELAY,		  BURST_SHOT_HIGH,		4,				25,					BLASTER_SPEED,		1.4f,					60,				128,			0,				0,					0,			},
	{ "DEMP 2",										500,		900,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	25,				35,					BLASTER_SPEED,		BLASTER_ACCURACY,		0,				256,			0,				250,				3,			},
	{ "Golan Arms Flechette",						700,		800,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	35,				45,					3500,				4.0f,					60,				128,			0,				0,					0,			},
	{ "Concussion Rifle",							800,		1200,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	50,				65,					3000,				BLASTER_ACCURACY,		65,				200,			0,				0,					0,			},
	//Place new Guns under here.												      																	
	{ "A280 Blaster",								250,		1500,			WFT_BURST,			MID_BURST_DELAY,		  BURST_SLOW_LOW,		2,				BLASTER_DAMAGE,		BLASTER_SPEED,		BLASTER_ACCURACY,		0,				0,				0,				0,					3,			},
	{ "T-21 Blaster Rifle",							175,		1200,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	BLASTER_DAMAGE, BLASTER_DAMAGE,		BLASTER_SPEED,		BLASTER_ACCURACY,		0,				0,				0,				100,				0,			},
	{ "EE-3 Blaster Rifle",							250,		1200,			WFT_BURST,			HIGH_BURST_DELAY,		  BURST_SHOT_MID,		2,				BLASTER_DAMAGE,		BLASTER_SPEED,		BLASTER_ACCURACY,		0,				0,				0,				0,					0,			},
	{ "DLT-19 Heavy Blaster Rifle",					175,		1200,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	BLASTER_DAMAGE, BLASTER_DAMAGE,		BLASTER_SPEED,		BLASTER_ACCURACY,		0,				0,				0,				0,					0,			},
	{ "DC-15A_Rifle",								150,		900,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	2,				50,					BLASTER_SPEED,		BLASTER_ACCURACY,		50,				128,			0,				250,				3,			},
	{ "Z-6 Rotary Blaster Cannon",					125,		2800,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	BLASTER_DAMAGE, BLASTER_DAMAGE,		BLASTER_SPEED,		BLASTER_ACCURACY,		0,				0,				0,				0,					0,			},
	{ "Bryar Carbine Blaster",						350,		250,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	BLASTER_DAMAGE, BLASTER_DAMAGE,		BLASTER_SPEED,		BLASTER_ACCURACY,		0,				0,				0,				200,				3,			},
	{ "Bryar Rifle",								275,		600,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	BLASTER_DAMAGE, BLASTER_DAMAGE,		BLASTER_SPEED,		BLASTER_ACCURACY,		0,				0,				0,				0,					0,			},
	{ "Bryar Sniper Rifle",							250,		1200,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	BLASTER_DAMAGE, BLASTER_DAMAGE,		BLASTER_SPEED,		BLASTER_ACCURACY,		0,				0,				0,				0,					0,			},
	{ "Pulse Canon",								200,		2800,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	BLASTER_DAMAGE, BLASTER_DAMAGE,		BLASTER_SPEED,		BLASTER_ACCURACY,		0,				0,				0,				0,					0,			},
	{ "Proton Carbine Rifle",						350,		275,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	BLASTER_DAMAGE, BLASTER_DAMAGE,		BLASTER_SPEED,		BLASTER_ACCURACY,		0,				0,				0,				200,				3,			},
	{ "DH-17 Pistol",								325,		275,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	PISTOL_DMG,		PISTOL_DMG,			PISTOL_SPEED,		PISTOL_ACCURACY,		0,				0,				0,				200,				3,			},
	//Old Weapons. do not add anything under here only above where new guns is added. Stoiss - UQ1: Grenades should be below here.
	{ "Merr-Sonn Missile System",					3000,		5000,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	ROCKET_DAMAGE,	ROCKET_DAMAGE,		1100,				0,						65,				160,			0,				0,					0,			},
	{ "Thermal Detonator",							800,		400,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	GRENADE_DAMAGE,	GRENADE_DAMAGE,		GRENADE_SPEED,		0,						90,				128,			0,				0,					0,			},
	{ "Frag Grenade",								800,		400,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	GRENADE_DAMAGE,	GRENADE_DAMAGE,		GRENADE_SPEED,		0,						90,				128,			0,				0,					0,			},
	{ "Old Frag Grenade",							800,		400,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	GRENADE_DAMAGE,	GRENADE_DAMAGE,		GRENADE_SPEED,		0,						90,				128,			0,				0,					0,			},
	{ "CryoBan Grenade",							800,		400,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	GRENADE_DAMAGE,	GRENADE_DAMAGE,		GRENADE_SPEED,		0,						90,				128,			0,				0,					0,			},
	{ "Trip Mine",									800,		400,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	GRENADE_DAMAGE,	GRENADE_DAMAGE,		GRENADE_SPEED,		0,						0,				0,				0,				0,					0,			},
	{ "Det Pack",									800,		400,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	GRENADE_DAMAGE,	GRENADE_DAMAGE,		GRENADE_SPEED,		0,						0,				0,				0,				0,					0,			},
	{ "Emplaced Gun",								100,		100,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	BLASTER_DAMAGE, BLASTER_DAMAGE,		BLASTER_SPEED,		BLASTER_ACCURACY,		0,				0,				0,				0,					0,			},
	{ "Turret",										100,		100,			WFT_AUTO,			DEFAULT_BURST_DELAY,	  DEFAULT_BURST_SHOT,	BLASTER_DAMAGE, BLASTER_DAMAGE,		BLASTER_SPEED,		BLASTER_ACCURACY,		0,				0,				0,				0,					0,			},

	};

qboolean WeaponIsGrenade(int weapon)
{
	if (weapon >= WP_THERMAL && weapon <= WP_DET_PACK)
	{
		return qtrue;
	}

	return qfalse;
}

qboolean WeaponIsRocketLauncher(int weapon)
{
	switch (weapon)
	{
	case WP_ROCKET_LAUNCHER:
		return qtrue;
	default:
		break;
	}

	return qfalse;
}

qboolean WeaponIsPistol(int weapon)
{
	switch (weapon)
	{
	case WP_BRYAR_PISTOL:
	case WP_BRYAR_OLD:
	case WP_THERMAL:
	case WP_FRAG_GRENADE:
	case WP_FRAG_GRENADE_OLD:
	case WP_CYROBAN_GRENADE:
		return qtrue;
	default:
		break;
	}

	return qfalse;
}

qboolean IsRollWithPistols(int weapon)
{
	switch (weapon)
	{
	case WP_BRYAR_PISTOL:
	case WP_BRYAR_OLD:
	case WP_THERMAL:
	case WP_FRAG_GRENADE:
	case WP_FRAG_GRENADE_OLD:
	case WP_CYROBAN_GRENADE:
		return qtrue;
	default:
		break;
	}

	return qfalse;
}
qboolean WeaponIsSniper(int weapon)
{
	switch (weapon)
	{
	case WP_DISRUPTOR:
	case WP_DLT_19:
	case WP_BRYAR_RIFLE_SCOPE:
	case WP_A280:
	case WP_EE3:
	case WP_DH_17_PISTOL:
		return qtrue;
	default:
		break;
	}

	return qfalse;
}
//theses weapons have charge option if they not are listed under the WeaponIsSniperNoCharge function.
qboolean WeaponIsSniperCharge(int weapon)
{
	switch (weapon)
	{
	case WP_DISRUPTOR:
	case WP_DLT_19:
	case WP_BRYAR_RIFLE_SCOPE:
		return qtrue;
	default:
		break;
	}

	return qfalse;
}
// theses weapons only have scopes with no charge options.
qboolean WeaponIsSniperNoCharge ( int weapon )
{
	switch (weapon)
	{
	case WP_A280:
	case WP_EE3:
	case WP_DH_17_PISTOL:
		return qfalse;
	default:
		break;
	}

	return qtrue;
}

qboolean BG_HaveWeapon ( const playerState_t *ps, int weapon )
{
	if (ps->primaryWeapon == weapon && weapon <= WP_NUM_USEABLE) return qtrue;
	if (ps->secondaryWeapon == weapon && weapon <= WP_NUM_USEABLE) return qtrue;
	if (ps->temporaryWeapon == weapon && weapon <= WP_NUM_USEABLE) return qtrue;
	if (ps->temporaryWeapon == WP_ALL_WEAPONS && weapon <= WP_NUM_USEABLE) return qtrue;

	return qfalse;
}

qboolean HaveWeapon ( playerState_t *ps, int weapon )
{
	if (ps->primaryWeapon == weapon && weapon <= WP_NUM_USEABLE) return qtrue;
	if (ps->secondaryWeapon == weapon && weapon <= WP_NUM_USEABLE) return qtrue;
	if (ps->temporaryWeapon == weapon && weapon <= WP_NUM_USEABLE) return qtrue;
	if (ps->temporaryWeapon == WP_ALL_WEAPONS && weapon <= WP_NUM_USEABLE) return qtrue;

	return qfalse;
}

// NOTE: "" means unused/ignore
scopeData_t scopeData[] = {
	// char	scopename[64],							char scopeModel[128],							char scopeModelShader[128],				char gunMaskShader[128],								char	maskShader[128],								char	insertShader[128],					char	lightShader[128],						char	tickShader[128],				char	chargeShader[128],				int scopeViewX,	int scopeViewY,	int scopeViewW,	int scopeViewH,		char	zoomStartSound[128],				char	zoomEndSound[128]					qboolean instantZoom,	float scopeZoomMin	float scopeZoomMax	float scopeZoomSpeed							
	"No Scope",										"",												"",										"",														"",														"",											"",												"",										"",										0,				0,				640,			480,				"",											"",											qtrue,					1.0f,				1.0f,				0.0f,							
	"Binoculars",									"",												"",										"",														"",														"",											"",												"",										"",										0,				0,				640,			480,				"sound/interface/zoomstart.wav",			"sound/interface/zoomend.wav",				qfalse,					1.5f,				3.0f,				0.1f,							
	"Short Range Viewfinder",						"",												"",										"",														"",														"",											"",												"",										"",										0,				0,				640,			480,				"",											"",											qtrue,					1.2f,				2.0f,				0.0f,							
	"Mid Range Viewfinder",							"",												"",										"",														"",														"",											"",												"",										"",										0,				0,				640,			480,				"",											"",											qtrue,					1.5f,				5.0f,				0.0f,							
	"Tenloss Disruptor Scope",						"",												"",										"",  													"gfx/2d/cropCircle2",									"gfx/2d/cropCircle",						"gfx/2d/cropCircleGlow",						"gfx/2d/insertTick",					"gfx/2d/crop_charge",					128,			50,				382,			382,				"sound/weapons/disruptor/zoomstart.wav",	"sound/weapons/disruptor/zoomend.wav",		qfalse,					3.0f,				3.0f,				0.2f,							
	"Blastech Bowcaster Scope",						"",												"",										"",														"gfx/2d/bowMask",										"gfx/2d/bowInsert",							"",												"",										"",										0,				0,				0,				0,					"sound/weapons/disruptor/zoomstart.wav",	"sound/weapons/disruptor/zoomend.wav",		qfalse,					1.2f,				1.2f,				0.4f,							
	"Blastech EE3 Scope",							"",												"",										"",														"gfx/2d/fett/cropCircle2",								"gfx/2d/fett/cropCircle",					"gfx/2d/fett/cropCircleGlow",					"",										"gfx/2d/fett/crop_charge",				0,				0,				640,			480,				"sound/weapons/disruptor/zoomstart.wav",	"sound/weapons/disruptor/zoomend.wav",		qfalse,					1.5f,				1.5f,				0.3f,							
	"Blastech A280 Scope",							"",												"",										"gfx/2D/arcMask",										"gfx/2d/a280cropCircle2",								"gfx/2d/a280cropCircle",					"",												"",										"",										134,			56,				364,			364,				"sound/weapons/disruptor/zoomstart.wav",	"sound/weapons/disruptor/zoomend.wav",		qfalse,					1.5f,				1.5f,				0.2f,							
	"Blastech DLT 19 Scope",						"",												"",										"gfx/2d/DLT-19_HeavyBlaster/scope_mask_overlay",		"gfx/2d/DLT-19_HeavyBlaster/scope_mask",				"gfx/2d/a280cropCircle",					"",												"",										"",										134,			56,				364,			364,				"sound/weapons/disruptor/zoomstart.wav",	"sound/weapons/disruptor/zoomend.wav",		qfalse,					2.5f,				2.5f,				0.2f,							
	"BlastTech ACP HAMaR Scope",					"",												"",										"gfx/2d/acp_sniperrifle/scope_mask_overlay",			"gfx/2d/acp_sniperrifle/scope_mask",					"",											"",												"",										"",										162,			20,				316,			440,				"sound/weapons/disruptor/zoomstart.wav",	"sound/weapons/disruptor/zoomend.wav",		qfalse,					1.5f,				5.0f,				0.2f,							
	"BlastTech Rifle Bowcaster Scope",				"",												"",										"",														"gfx/2d/Bowcaster/lensmask",							"gfx/2d/Bowcaster/lensmask_zoom",			"",												"",										"",										0,				0,				640,			480,				"sound/weapons/disruptor/zoomstart.wav",	"sound/weapons/disruptor/zoomend.wav",		qtrue,					1.2f,				1.2f,				0.0f,							
	"BlastTech Rifle Heavy Bowcaster Scope",		"",												"",										"gfx/2d/Bowcaster_Heavy/scope_mask_overlay",			"gfx/2d/Bowcaster_Heavy/scope_mask",					"",											"",												"",										"",										0,				0,				640,			480,				"sound/weapons/disruptor/zoomstart.wav",	"sound/weapons/disruptor/zoomend.wav",		qtrue,					1.2f,				1.2f,				0.0f,							
	"BlastTech Bryar Sniper Scope",					"",												"",										"",														"gfx/2d/Bryar_Rifle/scope_mask",						"",											"",												"",										"",										112,			36,				414,			414,				"sound/weapons/disruptor/zoomstart.wav",	"sound/weapons/disruptor/zoomend.wav",		qfalse,					1.5f,				1.5f,				0.2f,							
	"BlastTech DH-17 Pistol Scope",					"",												"",										"gfx/2d/DH-17_Pistol/scope_mask_overlay",				"gfx/2d/DH-17_Pistol/scope_mask",						"",											"",												"",										"",										0,				0,				640,			480,				"sound/weapons/disruptor/zoomstart.wav",	"sound/weapons/disruptor/zoomend.wav",		qtrue,					1.0f,				1.0f,				0.0f,							
};

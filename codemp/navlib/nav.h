/*
===========================================================================
Copyright (C) 2016-2017 Unique One

This file is part of the Warzone navlib source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

// nav.h -- navigation mesh definitions
#ifndef __NAV_H
#define __NAV_H

#include "navlib_api.h"
#include "fastlz/fastlz.h"
#include "navlib_convert.h"

// should be the same as in rest of engine
#define STEPSIZE 18
#define MIN_WALK_NORMAL 0.7f

static const int NAVMESHSET_MAGIC = 'M'<<24 | 'S'<<16 | 'E'<<8 | 'T'; //'MSET';
static const int NAVMESHSET_VERSION = 3;

struct NavMeshSetHeader
{
	int magic;
	int version;
	int numTiles;
	dtNavMeshParams params;
	dtTileCacheParams cacheParams;
};

struct NavMeshTileHeader
{
	dtCompressedTileRef tileRef;
	int dataSize;
};

template<class T> static inline void SwapArray( T block[], size_t len )
{
	if ( LittleLong( 1 ) != 1 )
	{
		for ( size_t i = 0; i < len; i++ )
		{
			dtSwapEndian( &block[ i ] );
		}
	}
}

static inline void SwapNavMeshSetHeader( NavMeshSetHeader &header )
{
	SwapArray( ( unsigned int * ) &header, sizeof( header ) / sizeof( unsigned int ) );
}

static inline void SwapNavMeshTileHeader( NavMeshTileHeader &header )
{
	if ( LittleLong( 1 ) != 1 )
	{
		dtSwapEndian( &header.dataSize );
		dtSwapEndian( &header.tileRef );
	}
}

static const int NAVMESHCON_VERSION = 2;
struct OffMeshConnectionHeader
{
	int version;
	int numConnections;
};

struct OffMeshConnection
{
	rVec  start;
	rVec  end;
	float radius;
	unsigned short flag;
	unsigned char area;
	unsigned char dir;
	unsigned int userid;
};

struct OffMeshConnections
{
	static CONSTEXPR int MAX_CON = 128;
	float  verts[ MAX_CON * 6 ];
	float  rad[ MAX_CON ];
	unsigned short flags[ MAX_CON ];
	unsigned char areas[ MAX_CON ];
	unsigned char dirs[ MAX_CON ];
	unsigned int userids[ MAX_CON ];
	int      offMeshConCount;

	OffMeshConnections() : offMeshConCount( 0 ) { }

	void reset()
	{
		offMeshConCount = 0;
	}

	void delConnection( int index )
	{
		if ( index < 0 || index >= offMeshConCount )
		{
			return;
		}

		for ( int i = index * 6; i < offMeshConCount * 6 - 1; i++ )
		{
			verts[ i ] = verts[ i + 1 ];
		}

		for ( int i = index; i < offMeshConCount - 1; i++ )
		{
			rad[ i ] = rad[ i + 1 ];
			flags[ i ] = flags[ i + 1 ];
			areas[ i ] = areas[ i + 1 ];
			dirs[ i ] = dirs[ i + 1 ];
			userids[ i ] = userids[ i + 1 ];
		}
		offMeshConCount--;
	}

	bool addConnection( const OffMeshConnection &c )
	{
		if ( offMeshConCount == MAX_CON )
		{
			return false;
		}

		float *start = &verts[ offMeshConCount * 6 ];
		float *end = start + 3;

		start[ 0 ] = c.start[ 0 ];
		start[ 1 ] = c.start[ 1 ];
		start[ 2 ] = c.start[ 2 ];
		end[ 0 ] = c.end[ 0 ];
		end[ 1 ] = c.end[ 1 ];
		end[ 2 ] = c.end[ 2 ];

		rad[ offMeshConCount ] = c.radius;
		flags[ offMeshConCount ] = c.flag;
		areas[ offMeshConCount ] = c.area;
		dirs[ offMeshConCount ] = c.dir;
		userids[ offMeshConCount ] = c.userid;

		offMeshConCount++;
		return true;
	}
};

struct FastLZCompressor : public dtTileCacheCompressor
{
	virtual int maxCompressedSize( const int bufferSize )
	{
		return ( int ) ( bufferSize * 1.05f );
	}

	virtual dtStatus compress( const unsigned char *buffer, const int bufferSize,
							   unsigned char *compressed, const int /*maxCompressedSize*/, int *compressedSize )
	{

		*compressedSize = fastlz_compress( ( const void *const ) buffer, bufferSize, compressed );
		return DT_SUCCESS;
	}

	virtual dtStatus decompress( const unsigned char *compressed, const int compressedSize,
								 unsigned char *buffer, const int maxBufferSize, int *bufferSize )
	{
		*bufferSize = fastlz_decompress( compressed, compressedSize, buffer, maxBufferSize );
		return *bufferSize < 0 ? DT_FAILURE : DT_SUCCESS;
	}
};

struct MeshProcess : public dtTileCacheMeshProcess
{
	OffMeshConnections con;

	virtual void process( struct dtNavMeshCreateParams *params, unsigned char *polyAreas, unsigned short *polyFlags )
	{
		// Update poly flags from areas.
		for ( int i = 0; i < params->polyCount; ++i )
		{
			if ( polyAreas[ i ] == DT_TILECACHE_WALKABLE_AREA )
			{
				polyAreas[ i ] = navlibPolyAreas::POLYAREA_GROUND;
				polyFlags[ i ] = navlibPolyFlags::POLYFLAGS_WALK;
			}
			else if ( polyAreas[ i ] == navlibPolyAreas::POLYAREA_WATER )
			{
				polyFlags[ i ] = navlibPolyFlags::POLYFLAGS_SWIM;
			}
			else if ( polyAreas[ i ] == navlibPolyAreas::POLYAREA_DOOR )
			{
				polyFlags[ i ] = navlibPolyFlags::POLYFLAGS_WALK | navlibPolyFlags::POLYFLAGS_DOOR;
			}
		}

		params->offMeshConVerts = con.verts;
		params->offMeshConRad = con.rad;
		params->offMeshConCount = con.offMeshConCount;
		params->offMeshConAreas = con.areas;
		params->offMeshConDir = con.dirs;
		params->offMeshConFlags = con.flags;
		params->offMeshConUserID = con.userids;
	}
};

struct LinearAllocator : public dtTileCacheAlloc
{
	unsigned char* buffer;
	size_t capacity;
	size_t top;
	size_t high;

	LinearAllocator( const size_t cap ) : buffer(0), capacity(0), top(0), high(0)
	{
		resize(cap);
	}

	~LinearAllocator() OVERRIDE
	{
		free( buffer );
	}

	void resize( const size_t cap )
	{
		if ( buffer )
		{
			free( buffer );
		}

		buffer = ( unsigned char* ) malloc( cap );
		capacity = cap;
	}

	void reset() OVERRIDE
	{
		high = dtMax( high, top );
		top = 0;
	}

	void* alloc( const size_t size ) //OVERRIDE
	{
		if ( !buffer )
		{
			return 0;
		}

		if ( top + size > capacity )
		{
			return 0;
		}

		unsigned char* mem = &buffer[ top ];
		top += size;
		return mem;
	}

	void free( void* /*ptr*/ ) OVERRIDE { }
	size_t getHighSize() { return high; }
};
#endif


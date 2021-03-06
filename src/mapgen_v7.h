/*
mapgen_v7.h
Copyright (C) 2010-2015 kwolekr, Ryan Kwolek <kwolekr@minetest.net>
Copyright (C) 2010-2015 paramat, Matt Gregory
*/

/*
This file is part of Freeminer.

Freeminer is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Freeminer  is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Freeminer.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAPGEN_V7_HEADER
#define MAPGEN_V7_HEADER

#include "mapgen.h"
#include "mapgen_indev.h"

/////////////////// Mapgen V7 flags
#define MGV7_MOUNTAINS   0x01
#define MGV7_RIDGES      0x02

class BiomeManager;

extern FlagDesc flagdesc_mapgen_v7[];


struct MapgenV7Params : public MapgenParams {
	u32 spflags;
	float cave_width;
	NoiseParams np_terrain_base;
	NoiseParams np_terrain_alt;
	NoiseParams np_terrain_persist;
	NoiseParams np_height_select;
	NoiseParams np_filler_depth;
	NoiseParams np_mount_height;
	NoiseParams np_ridge_uwater;
	NoiseParams np_mountain;
	NoiseParams np_ridge;
	NoiseParams np_cave1;
	NoiseParams np_cave2;

	s16 float_islands;
	NoiseParams np_float_islands1;
	NoiseParams np_float_islands2;
	NoiseParams np_float_islands3;
	NoiseParams np_layers;
	//NoiseParams np_cave_indev;
	Json::Value paramsj;

	MapgenV7Params();
	~MapgenV7Params() {}

	void readParams(Settings *settings);
	void writeParams(Settings *settings) const;
};

class MapgenV7 : public MapgenBasic, public Mapgen_features {
public:
	MapgenV7(int mapgenid, MapgenV7Params *params, EmergeManager *emerge);
	~MapgenV7();

	virtual MapgenType getType() const { return MAPGEN_V7; }

	virtual void makeChunk(BlockMakeData *data);
	int getSpawnLevelAtPoint(v2s16 p);

	float baseTerrainLevelAtPoint(s16 x, s16 z);
	float baseTerrainLevelFromMap(int index);
	bool getMountainTerrainAtPoint(s16 x, s16 y, s16 z);
	bool getMountainTerrainFromMap(int idx_xyz, int idx_xz, s16 y);
	virtual int generateTerrain();
	virtual void generateRidgeTerrain();

private:
	Noise *noise_terrain_base;
	Noise *noise_terrain_alt;
	Noise *noise_terrain_persist;
	Noise *noise_height_select;
	Noise *noise_mount_height;
	Noise *noise_ridge_uwater;
	Noise *noise_mountain;
	Noise *noise_ridge;

	//freeminer:
	s16 float_islands;
	virtual void generateExperimental();
	//=========

};

#endif

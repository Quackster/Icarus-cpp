/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <mutex>

class Room;
class Item;
class DynamicModel
{

public:
	DynamicModel(Room *room);

	void load();
	void unload();

	void regenerateCollisionMaps();
	void addTileStates(int &index, double stack_height, bool valid);
	int &getSearchIndex(int x, int y);

	Item *getItemAtPosition(int x, int y);

	double &getTileHeight(int x, int y) const { return tile_height[x * map_size_y + y]; }

	const bool &isValidTile(int x, int y) const {

		if (x >= this->map_size_x || !(x >= 0)) {
			return 0;
		}

		if (y >= this->map_size_y || !(y >= 0)) {
			return 0;
		}

		return tile_flags[x * map_size_y + y] == 0;
	}

	~DynamicModel();

private:
	Room *room;
	std::mutex mtx;

	Item **items = nullptr;	
	int *tile_flags = nullptr;
	double *tile_height = nullptr;

	int map_size_x;
	int map_size_y;
};


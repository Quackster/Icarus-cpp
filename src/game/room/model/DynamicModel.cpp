/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"
#include "DynamicModel.h"

#include "game/room/Room.h"

#include "game/item/Item.h"
#include "game/item/definitions/ItemDefinition.h"

/*
	The constructor for DynamicModel
*/
DynamicModel::DynamicModel(Room *room) :
	room(room) {

	this->map_size_x = room->getModel()->map_size_x;
	this->map_size_y = room->getModel()->map_size_y;
}


/*
	Create the multi-dimensional arrays for storing data about each tile

	@return none
*/
void DynamicModel::load() {
	this->items = new Item*[map_size_x * map_size_y];
	this->tile_flags = new int[map_size_x * map_size_y];
	this->tile_height = new double[map_size_x * map_size_y];

	this->regenerateCollisionMaps();
}

/*
	Returns an item at a given position, will return nullptr
	if no item was found, will include the item's affected tiles

	@param x coordinate
	@param y coordinate
	@return Item pointer
*/
Item *DynamicModel::getItemAtPosition(int x, int y) {
	return this->items[this->getSearchIndex(x, y)];
}

/*
	Regenerate the collision mapping for the pathfinder and set the items
	to the array for lookup purposes

	@return none
*/
void DynamicModel::regenerateCollisionMaps() {

	this->unload();

	for (int y = 0; y < map_size_y; y++) {
		for (int x = 0; x < map_size_x; x++) {

			int index = this->getSearchIndex(x, y);

			this->tile_flags[index] = room->getModel()->squares[index];
			this->tile_height[index] = room->getModel()->square_height[index];
			this->items[index] = nullptr;
		}
	}

	for (Item *item : this->room->getItems()) {

		int index = this->getSearchIndex(item->x, item->y);

		this->items[index] = item;

		bool valid = false;

		if (item->getDefinition()->can_sit) {
			valid = true;
		}

		if (item->getDefinition()->is_walkable) {
			valid = true;
		}

		if (item->getDefinition()->interaction_type == "bed") {
			valid = true;
		}

		if (valid) {
			this->tile_flags[index] = RoomModel::OPEN;
		}
		else {
			this->tile_flags[index] = RoomModel::CLOSED;
			this->tile_height[index] += item->getDefinition()->stack_height;
		}

		for (auto kvp : item->getAffectedTiles()) {

			int new_index = this->getSearchIndex(kvp.second.x, kvp.second.y);
			this->items[new_index] = item;

			if (valid) {
				this->tile_flags[new_index] = RoomModel::OPEN;
			}
			else {
				this->tile_flags[new_index] = RoomModel::CLOSED;
				this->tile_height[new_index] += item->getDefinition()->stack_height;
			}
		}
	}
}

/*
	Creates the search index for array lookup with the given 
	x and y coordinates (very fast lookup method!) :)

	@param x coordinate
	@param y coordinate
	@return array lookup index formula
*/
int DynamicModel::getSearchIndex(int x, int y) {
	return (x * this->map_size_y) + y;
}

/*
	Deletes all arrays, as they are pointers which require to be
	deleted once they're no longer used

	@return none
*/
void DynamicModel::unload() {

	if (this->items != nullptr) {
		delete this->items;
	}

	if (this->tile_flags != nullptr) {
		delete this->tile_flags;
	}

	if (this->tile_height != nullptr) {
		delete this->tile_height;
	}

}

/*
	Deconstructor for DynamicModel
*/
DynamicModel::~DynamicModel() {
	this->unload();
}

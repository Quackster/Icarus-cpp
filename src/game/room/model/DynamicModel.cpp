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

}

/*
	Returns an item at a given position, will return nullptr
	if no item was found, will include the item's affected tiles

	@param x coordinate
	@param y coordinate
	@return Item pointer
*/
Item *DynamicModel::getItemAtPosition(int x, int y) {

	std::vector<Item*> items = room->getItems(FLOOR_ITEM);

	for (int i = 0; i < items.size(); i++) {

		Item *item = items.at(i);

		if (item == nullptr) {
			continue;
		}

		if (item->x == x && item->y == y) {
			return item;
		}

		for (auto kvp : item->getAffectedTiles()) {

			if (kvp.second.x == x && kvp.second.y == y) {
				return item;
			}
		}
	}

	return nullptr;
}

std::vector<Item*> DynamicModel::getItemsAtPosition(int x, int y, bool single_tile) {

	std::vector<Item*> found_items;
	std::vector<Item*> items = room->getItems(FLOOR_ITEM);

	for (int i = 0; i < items.size(); i++) {

		Item *item = items.at(i);

		if (item == nullptr) {
			continue;
		}

		if (item->x == x && item->y == y) {
			found_items.push_back(item);
		}
		else {

			if (!single_tile) {

				for (auto kvp : item->getAffectedTiles()) {

					if (kvp.second.x == x && kvp.second.y == y) {
						found_items.push_back(item);
					}
				}
			}
		}
	}

	return found_items;
}


double DynamicModel::getTileHeight(int x, int y) {//const { return tile_height[x * map_size_y + y]; }

	double final_height = room->getModel()->getSquareHeight(x, y);

	std::vector<Item*> items = this->getItemsAtPosition(x, y, true);

	for (int i = 0; i < items.size(); i++) {

		Item *item = items.at(i);

		if (item == nullptr) {
			continue;
		}

		final_height += item->getDefinition()->stack_height;

	}

	return final_height;
}

bool DynamicModel::isValidTile(int x, int y) {

	bool valid = false;

	Item *item = this->getItemAtPosition(x, y);

	if (item == nullptr) {
		return true;
	}

	if (item->getDefinition()->can_sit) {
		valid = true;
	}

	if (item->getDefinition()->is_walkable) {
		valid = true;
	}

	if (item->getDefinition()->interaction_type == "bed") {
		valid = true;
	}

	return valid;
}

/*
	Creates the search index for array lookup with the given 
	x and y coordinates (very fast lookup method!) :)

	@param x coordinate
	@param y coordinate
	@return array lookup index formula
*/
int DynamicModel::getSearchIndex(int x, int y) {
	return x * this->map_size_y + y;
}

/*
	Deconstructor for DynamicModel
*/
DynamicModel::~DynamicModel() {

}

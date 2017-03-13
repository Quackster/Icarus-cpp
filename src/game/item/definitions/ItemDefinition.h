/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <string>

struct ItemDefinition {
	int id;
	std::string public_name;
	std::string item_name;
	std::string type;
	int width;
	int length;
	double stack_height;
	bool can_stack;
	bool can_sit;
	bool is_walkable;
	int sprite_id = -1;
	bool allow_recycle;
	bool allow_trade;
	bool allow_marketplace_sell;
	bool allow_gift;
	bool allow_inventory_stack;
	std::string interaction_type;
	bool interaction_modes_count;
	int vending_id;
	int effect_id;
	int height_adjustible;
	int flat_id;
	int song_id;
	bool requires_rights;
	bool is_arrow;
};
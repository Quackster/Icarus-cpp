/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "game/item/definitions/ItemDefinition.h"

class Item
{
public:
	Item(int id, int user_id, int item_id, int room_id, int x, int y, int z, std::string extra_data);
	~Item();

	bool isWallItem();

	ItemDefinition *getDefinition() { return this->item_definition; }

	int id = -1;
	int user_id = -1;
	int item_id = -1;
	int room_id = -1;
	int x = -1;
	int y = -1;
	int z = -1; 
	std::string extra_data = "";

private:
	ItemDefinition *item_definition = nullptr;
};


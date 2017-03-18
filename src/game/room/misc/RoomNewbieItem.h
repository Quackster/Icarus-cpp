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
#include <vector>

class ItemDefinition;
struct RoomNewbieItem {

	int item_id;
	std::string position;
	
	int x = -1;
	int y = -1;
	int z;

	ItemDefinition *definition;
};
/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <vector>
#include "game/furniture/Furniture.h"

class FurnitureManager
{
public:
	FurnitureManager();
	~FurnitureManager();

	Furniture getFurnitureByID(int item_id);
	Furniture getFurnitureBySpriteID(int item_id);

private:
	std::map<int, Furniture> id_lookup;
	std::map<int, Furniture> sprite_lookup;
};


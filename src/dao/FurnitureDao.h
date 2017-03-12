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
#include <map>

#include <string>
#include "game/furniture/Furniture.h"

class FurnitureDao
{

private:
	FurnitureDao() { };

public:
    static std::map<int, Furniture> getFurniture();
};


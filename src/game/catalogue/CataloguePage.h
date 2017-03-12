/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "game/catalogue/CatalogueItem.h"

#include <vector>

struct CataloguePage {
	int id = -1;
	std::string caption;
	int parent_id = -1;
	std::string type;
	std::string layout;
	int minimum_rank;

	std::vector<std::string> images;
	std::vector<std::string> texts;
	std::vector<CatalogueItem> items;
};
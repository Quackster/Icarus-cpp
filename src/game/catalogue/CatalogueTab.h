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

struct CatalogueTab
{
	int id;
	int parent_id;
	std::string caption;
	int icon_colour;
	int icon_image;
	bool enabled;
	int min_rank;
	std::vector<CatalogueTab> *child_tabs = new std::vector<CatalogueTab>();
};


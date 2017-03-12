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

class CatalogueTab;
class CataloguePage;
class CatalogueItem;
class CatalogueDao
{

private:
    CatalogueDao() { };

public:
    static std::vector<CatalogueTab*> getTabs(int child_id);
	static std::map<int, CataloguePage*> getPages();
	static std::vector<CatalogueItem*> getItems();
};


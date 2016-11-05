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

#include "game/navigator/NavigatorTab.h"
#include "game/navigator/NavigatorCategory.h"

#include "game/navigator/populators/RoomPopulator.h"

class NavigatorManager
{
public:
    NavigatorManager();
    ~NavigatorManager();

    NavigatorTab *getTab(std::string tab_name);
    std::vector<NavigatorTab*> getParentTabs();
    NavigatorCategory *getCategoryById(int category_id);
    std::vector<NavigatorTab*> getTabs() { return tabs; }
    std::vector<NavigatorCategory*> getCategories() { return categories; }
    RoomPopulator *getPopulator(std::string name);
    

private:
    std::vector<NavigatorTab*> tabs;
    std::vector<NavigatorCategory*> categories;
    std::map<std::string, RoomPopulator*> room_populators;
};


/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "boot/Icarus.h"
#include "game/navigator/NavigatorTab.h"

/*
    Constructor for Navigator tab
*/
NavigatorTab::NavigatorTab(int id, int child_id, std::string tab_name, std::string title, char button_type, bool closed, bool thumbnail, std::string populator_name) :
    id(id), child_id(child_id), tab_name(tab_name), title(title), button_type(button_type), closed(closed), thumbnail(thumbnail), populator(populator_name) { }

/*
    Get all child tabs under this tab

    @return list of child tabs
*/
std::vector<NavigatorTab*> NavigatorTab::getChildTabs() {

    std::vector<NavigatorTab*> tabs = std::vector<NavigatorTab*>();

    for (auto tab : *Icarus::getGame()->getNavigatorManager()->getTabs()) {
        if (tab->getChildId() == this->id) {
            tabs.push_back(tab);
        }
    }

    return tabs;
}


/*
    Deconstructor for navigator tab
*/
NavigatorTab::~NavigatorTab()
{
}

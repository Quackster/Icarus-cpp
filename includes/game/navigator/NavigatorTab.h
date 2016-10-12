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

class NavigatorTab
{
public:
    NavigatorTab(int id, int childId, std::string tab_name, std::string title, char button_type, bool closed, bool thumbnail, std::string populator);
    ~NavigatorTab();

    std::vector<NavigatorTab*> getChildTabs();

    int getId() { return id; }
    int getChildId() { return child_id; }
    std::string getTabName() { return tab_name; }
    std::string getTitle() { return title; }
    char getButtonType() { return button_type; }
    bool getClosed() { return closed; }
    bool getThumbnail() { return thumbnail; }
    std::string getPopulatorName() { return populator; }

private:
    int id;
    int child_id;
    std::string tab_name;
    std::string title;
    char button_type;
    bool closed;
    bool thumbnail;
    std::string populator;
};


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

    const int &getId() const { return id; }
    const int &getChildId() const { return child_id; }
    const std::string &getTabName() const { return tab_name; }
    const std::string &getTitle() const { return title; }
    const char &getButtonType() const { return button_type; }
    const bool &getClosed() const { return closed; }
    const bool &getThumbnail() const { return thumbnail; }
    const std::string &getPopulatorName() const { return populator; }

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


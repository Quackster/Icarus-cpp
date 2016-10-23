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

class NavigatorCategory
{
public:
    NavigatorCategory(int id, std::string name, int minimum_rank);
    ~NavigatorCategory();
    int getId() { return id; }
    std::string getName() { return name; }
    int getMinimumRank() { return minimum_rank;  }

private:
    int id;
    std::string name;
    int minimum_rank;

};


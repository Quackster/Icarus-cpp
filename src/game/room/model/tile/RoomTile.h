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

class Item;
class RoomTile {

public:
    RoomTile();
    ~RoomTile();

    std::vector<Item*> items;
    Item *highest_item = nullptr;

    double height = 0.0;
};
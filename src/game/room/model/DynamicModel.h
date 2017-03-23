/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <mutex>
#include <vector>

#include "misc/Array2D.h"

class Room;
class Item;
class DynamicModel
{

public:
    DynamicModel(Room *room);

    void load();
    void regenerateCollisionMaps();
    Item *getItemAtPosition(int x, int y);
    void removeItem(Item *item);
    void addItem(Item *item);
    void updateItemPosition(Item *item, bool rotation_only = false);
    void handleItemAdjustment(Item *item, bool rotation_only = false);

    const double &getStackHeight(int x, int y) const { return stack_height[x][y]; }
    bool isValidTile(int x, int y);

    ~DynamicModel();

private:
    Room *room;
    std::mutex mtx;

    //Array2D<Item*> items;
    Array2D<Item*> highest_items;
    Array2D<double> stack_height;

    //int *tile_flags = nullptr;
    //double *tile_height = nullptr;

    int map_size_x;
    int map_size_y;
};


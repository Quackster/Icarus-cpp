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
    int getSearchIndex(int x, int y);
    void regenerateCollisionMaps();
    void addTileStates(int x, int y, double stack_height, bool valid);

    Item *getItemAtPosition(int x, int y);
    void removeItem(Item *item);
    void addItem(Item *item);
    void updateItemPosition(Item *item, bool calculate_height = true);
    void handleItemAdjustment(Item *item);

    double getTileHeight(int x, int y) const { return tile_height[x][y]; }
    double getStackHeight(int x, int y) const { return stack_height[x][y]; }
    bool isValidTile(int x, int y) const { return flags[x][y] == 0;    }

    ~DynamicModel();

private:
    Room *room;
    std::mutex mtx;

    Array2D<Item*> items;
    Array2D<int> flags;
    Array2D<double> tile_height;
    Array2D<double> stack_height;

    //int *tile_flags = nullptr;
    //double *tile_height = nullptr;

    int map_size_x;
    int map_size_y;
};


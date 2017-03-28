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
#include <map>

class Room;
class Item;
class RoomTile;
class DynamicModel
{

public:
    DynamicModel(Room *room);

    void load();
    void regenerateCollisionMaps();
    void checkHighestItem(Item *item, int x, int y);

    Item *getItem(int x, int y);
    RoomTile &getTile(int x, int y);
    double getStackHeight(int x, int y);

    void removeItem(Item *item);
    void addItem(Item *item);
    void updateItemPosition(Item *item, bool rotation_only = false);
    void handleItemAdjustment(Item *item, bool rotation_only = false);
    bool isValidTile(int x, int y);

    ~DynamicModel();

private:
    Room *room;
    std::map<int, std::map<int, RoomTile>> tiles;

    int map_size_x;
    int map_size_y;
};


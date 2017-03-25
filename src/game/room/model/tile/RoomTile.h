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
class Room;
class RoomTile {

public:
    RoomTile();
    RoomTile(Room *room);
    ~RoomTile();
    
    double height = 0.0;

    std::vector<Item*> &getItems();
    Item *getHighestItem();
    void setHighestItem(Item *item);
    

private:
    Room *room;
    std::vector<Item*> items;
    Item *highest_item;
};
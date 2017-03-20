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

#include "game/item/definitions/ItemType.h"

class Item;
class Player;
class Inventory {

public:
    Inventory(Player *player, std::vector<Item*> items);
    ~Inventory();

    void update();
    void addItem(Item *item);
    void removeItem(Item *item, bool delete_from_database = true);

    Item *getItem(int item_id);
    std::vector<Item*> getItems(ItemType type);
    std::vector<Item*> getItems() { return this->items; }

private:
    Player *player;
    std::vector<Item*> items;

};
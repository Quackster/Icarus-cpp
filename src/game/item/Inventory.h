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
class Inventory {

public:
    Inventory(std::vector<Item*> items);
    ~Inventory();

	std::vector<Item*> getItems() { return this->items; }

private:
    std::vector<Item*> items;

};
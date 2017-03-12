/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "Item.h"
#include "Inventory.h"

/*
    Constructor for Inventory

    @param list of inventory items
*/
Inventory::Inventory(std::vector<Item*> items) :
    items(items) { }

/*
    Deconstructor for invenotyr
*/
Inventory::~Inventory() {


}
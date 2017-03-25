/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/

#include "stdafx.h"

#include "RoomTile.h"
#include "game/room/Room.h"

/*
    Constructors for room tile

    @param Room pointer
*/
RoomTile::RoomTile() { }

RoomTile::RoomTile(Room *room) 
    : room(room) { }

/*
    Return the items list in this tile by reference

    @return vector Item ptr
*/
std::vector<Item*> &RoomTile::getItems() {
    return this->items;
}

/*
    Returns the highest Item found on this tile

    @return Item pointer
*/
Item *RoomTile::getHighestItem() {
    return this->highest_item;
}

/*
    Sets the highest item defined in this tile

    @param Item pointer
    @return none
*/
void RoomTile::setHighestItem(Item *item) {
    this->highest_item = item;
}

RoomTile::~RoomTile() { }
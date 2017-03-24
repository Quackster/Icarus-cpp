/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "DynamicModel.h"

#include "game/room/Room.h"
#include "tile/RoomTile.h"

#include "game/item/Item.h"
#include "game/item/definitions/ItemDefinition.h"

#include "communication/outgoing/room/item/RemoveItemMessageComposer.h"
#include "communication/outgoing/room/item/PlaceItemMessageComposer.h"
#include "communication/outgoing/room/item/MoveItemMessageComposer.h"

/*
    The constructor for DynamicModel
*/
DynamicModel::DynamicModel(Room *room) :
    room(room) {

    this->map_size_x = room->getModel()->map_size_x;
    this->map_size_y = room->getModel()->map_size_y;
}


/*
    Create the multi-dimensional arrays for storing data about each tile
    @return none
*/
void DynamicModel::load() {
    this->regenerateCollisionMaps();
}

/*
    Regenerate the collision mapping for the pathfinder and set the items
    to the array for lookup purposes
    @return none
*/
void DynamicModel::regenerateCollisionMaps() {


    for (int y = 0; y < map_size_y; y++) {
        for (int x = 0; x < map_size_x; x++) {
        }
    }

    std::vector<Item*> items = this->room->getItems(FLOOR_ITEM);

    for (int i = 0; i < items.size(); i++) {

        Item *item = items.at(i);

        if (item == nullptr) {
            continue;
        }

        double stacked_height = 0;

        if (item->getDefinition()->can_stack) {
            stacked_height = item->getDefinition()->height;
        }

        this->checkHighestItem(item, item->x, item->y);

        for (auto kvp : item->getAffectedTiles()) {

            this->checkHighestItem(item, kvp.second.x, kvp.second.y);
        }
    }
}

/*
    Checks to see if our given item is the highest or not
    if it is, then we set it, or there's no item defined, it's also set as the foundation
    to check upon
    
    @param Item instance
    @param x coordinate
    @param y coordinate
*/
void DynamicModel::checkHighestItem(Item *item, int x, int y) {


    if (highest_item == nullptr) {
    }
    else {
        if (item->z > highest_item->z) {
        }
    }
}

/*
    Checks against the database of items and room model if the
    requested tile is avaliable to walk on

    @param x coordinate
    @param y coordinate
    @return boolean: if tile is valid or not
*/
bool DynamicModel::isValidTile(int x, int y) {

    bool tile_valid = room->getModel()->isValidSquare(x, y);

    if (item != nullptr) {
        tile_valid = item->canWalk();
    }

    // This is returned when there's no items found, it will
    // just check the default model if the tile is valid
    return tile_valid;
}


/*
    Returns an item at a given position, will return nullptr
    if no item was found, will include the item's affected tiles

    @param x coordinate
    @param y coordinate
    @return Item pointer
*/
Item *DynamicModel::getItemAtPosition(int x, int y) {
}

/*
    Returns an tile instance at a given position

    @param x coordinate
    @param y coordinate
    @return RoomTile reference
*/
RoomTile &DynamicModel::getTileAtPosition(int x, int y) {
}

/*
    Returns the current tile height

    @param x coordinate
    @param y coordinate
    @return height in double type
*/
double DynamicModel::getStackHeight(int x, int y) {
}

/*
    Remove the item from the player's inventory

    @param Item ptr
    @return none
*/
void DynamicModel::removeItem(Item *item) {

    item->room_id = -1;
    item->x = -1;
    item->y = -1;
    item->z = 0;
    item->rotation = 0;
    item->extra_data = "";

    this->room->getItems().erase(std::remove(this->room->getItems().begin(), this->room->getItems().end(), item), this->room->getItems().end());
    this->room->send(RemoveItemMessageComposer(item));
    this->regenerateCollisionMaps();

    item->save();
}

/*
    Add the item to the room

    @param Item ptr
    @return none
*/
void DynamicModel::addItem(Item *item) {

    item->room_id = room->id;
    this->room->getItems().push_back(item);

    if (item->isFloorItem()) {
        this->handleItemAdjustment(item);
        this->regenerateCollisionMaps();
    }

    this->room->send(PlaceItemMessageComposer(item));
    item->save();
}

/*
    Update the position, must be in a room!

    @return none
*/
void DynamicModel::updateItemPosition(Item *item, bool rotation_only) {

    if (item->isFloorItem()) {
        this->handleItemAdjustment(item, rotation_only);
        this->room->getDynamicModel()->regenerateCollisionMaps();
    }

    item->updateStatus();
    item->save();
}

/*
    Deal with the stacking of items and general affected tiles if the item was moved or placed

    @param Item to handle
    @return none
*/
void DynamicModel::handleItemAdjustment(Item *item, bool rotation_only) {

    /*if (!rotation_only) {
        Item *found_item = this->getItemAtPosition(item->x, item->y);

        if (found_item != nullptr) {
            item->z = this->getStackHeight(item->x, item->y);
        }
        else {
            
        }
    }*/
item->z = this->getStackHeight(item->x, item->y);
    item->updateEntities();
}

/*
    Deconstructor for DynamicModel
*/
DynamicModel::~DynamicModel() {

}

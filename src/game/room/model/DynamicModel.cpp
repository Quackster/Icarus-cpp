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

#include "game/item/Item.h"
#include "game/item/definitions/ItemDefinition.h"

#include "communication/outgoing/room/item/RemoveItemMessageComposer.h"
#include "communication/outgoing/room/item/PlaceItemMessageComposer.h"
#include "communication/outgoing/room/item/MoveItemMessageComposer.h"


/*
    The constructor for DynamicModel
*/
DynamicModel::DynamicModel(Room *room) :
    room(room),
    items(Array2D<Item*>(0, 0)),
    flags(Array2D<int>(0, 0)),
    height(Array2D<double>(0, 0)) {

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

    this->items = Array2D<Item*>(this->map_size_x, this->map_size_y);
    this->flags = Array2D<int>(this->map_size_x, this->map_size_y);
    this->height = Array2D<double>(this->map_size_x, this->map_size_y);

    for (int y = 0; y < map_size_y; y++) {
        for (int x = 0; x < map_size_x; x++) {

            int index = this->getSearchIndex(x, y);

            this->flags[x][y] = room->getModel()->squares[index];
            this->height[x][y] = room->getModel()->square_height[index];
            this->items[x][y] = nullptr;
        }
    }

    std::vector<Item*> items = this->room->getItems(FLOOR_ITEM);

    for (int i = 0; i < items.size(); i++) {

        Item *item = items.at(i);

        if (item == nullptr) {
            continue;
        }

        this->items[item->x][item->y] = item;

        bool valid = false;

        if (item->getDefinition()->can_sit) {
            valid = true;
        }

        if (item->getDefinition()->is_walkable) {
            valid = true;
        }

        if (item->getDefinition()->interaction_type == "bed") {
            valid = true;
        }

        this->addTileStates(item->x, item->y, item->getDefinition()->stack_height, valid);

        for (auto kvp : item->getAffectedTiles()) {
            this->items[kvp.second.x][kvp.second.y] = item;
            this->addTileStates(kvp.second.x, kvp.second.y, item->getDefinition()->stack_height, valid);
        }
    }
}


/*
Add the title states (stack height, and whether or not the tile is valid)
@param x coordinate
@param y coordinate
@param stack height
@bool valid
*/
void DynamicModel::addTileStates(int x, int y, double stack_height, bool valid) {

    if (valid) {
        this->flags[x][y] = RoomModel::OPEN;
    }
    else {
        this->flags[x][y] = RoomModel::CLOSED;
        this->height[x][y] += stack_height;
    }
}
/*
    Returns an item at a given position, will return nullptr
    if no item was found, will include the item's affected tiles
    @param x coordinate
    @param y coordinate
    @return Item pointer
*/
Item *DynamicModel::getItemAtPosition(int x, int y) {
    return this->items[x][y];
}


/*
    Remove the item from the player's inventory

    @param Item ptr
    @return none
*/
void DynamicModel::removeItem(Item *item) {

    // Remove room id from item
    item->room_id = -1;
    item->save();

    // Remove from vector
    this->room->getItems().erase(std::remove(this->room->getItems().begin(), this->room->getItems().end(), item), this->room->getItems().end());

    // Alert item removed
    this->room->send(RemoveItemMessageComposer(item));

    // Regenerate collision map
    this->regenerateCollisionMaps();
}

/*
    Add the item to the room

    @param Item ptr
    @return none
*/
void DynamicModel::addItem(Item *item) {
    
    // Assign room id to item
    item->room_id = room->id;

    if (item->isFloorItem()) {
        item->updateEntities();
    }

    item->save();

    // Add item to room's known items
   this->room->getItems().push_back(item);

    // Show client the item was added
    this->room->send(PlaceItemMessageComposer(item));

    // Regenerate collision map
    this->regenerateCollisionMaps();
}

/*
    Update the position, must be in a room!

    @return none
*/
void DynamicModel::updateItemPosition(Item *item) {

    // Alert clients of item changes
    room->send(MoveItemMessageComposer(item));

    // Regenerate the collision map
    room->getDynamicModel()->regenerateCollisionMaps();
}

/*
    Creates the search index for array lookup with the given 
    x and y coordinates (very fast lookup method!) :)

    @param x coordinate
    @param y coordinate
    @return array lookup index formula
*/
int DynamicModel::getSearchIndex(int x, int y) {
    return x * this->map_size_y + y;
}

/*
    Deconstructor for DynamicModel
*/
DynamicModel::~DynamicModel() {

}

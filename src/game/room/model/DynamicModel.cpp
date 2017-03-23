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
    //items(Array2D<Item*>(0, 0)),
    highest_items(Array2D<Item*>(0, 0)),
    stack_height(Array2D<double>(0, 0)) {

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

    this->highest_items = Array2D<Item*>(this->map_size_x, this->map_size_y);
    this->stack_height = Array2D<double>(this->map_size_x, this->map_size_y);

    for (int y = 0; y < map_size_y; y++) {
        for (int x = 0; x < map_size_x; x++) {
            this->stack_height[x][y] = room->getModel()->getSquareHeight(x, y);
            this->highest_items[x][y] = nullptr;
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

        Item *highest_item = this->highest_items[item->x][item->y];

        if (highest_item == nullptr) {
            this->highest_items[item->x][item->y] = item;
        }
        else {
            if (item->z > highest_item->z) {
                this->highest_items[item->x][item->y] = item;
            }
        }
        
        this->stack_height[item->x][item->y] += stacked_height;

        for (auto kvp : item->getAffectedTiles()) {

            Item *highest_item = this->highest_items[kvp.second.x][kvp.second.y];

            if (highest_item == nullptr) {
                this->highest_items[kvp.second.x][kvp.second.y] = item;
            }
            else {
                if (item->z > highest_item->z) {
                    this->highest_items[kvp.second.x][kvp.second.y] = item;
                }
            }

            this->stack_height[kvp.second.x][kvp.second.y] += stacked_height;
        }
    }
}


bool DynamicModel::isValidTile(int x, int y) {

    Item *item = this->highest_items[x][y];

    bool valid = room->getModel()->isValidSquare(x, y);
    
    if (item != nullptr) {

        if (item->getDefinition()->can_sit) {
            valid = true;
        }
        else {
            valid = false;
        }

        if (item->getDefinition()->interaction_type == "bed") {
            valid = true;
        }
        else {
            valid = false;
        }

        if (item->getDefinition()->is_walkable) {
            valid = true;
        }
        else {
            valid = false;
        }

        if (item->getDefinition()->interaction_type == "gate") {
            if (item->extra_data == "1") {
                valid = true;
            }
            else {
                valid = false;
            }
        }

    }


    return valid;
}


/*
    Add the title states (stack height, and whether or not the tile is valid)
    @param x coordinate
    @param y coordinate
    @param stack height
    @bool valid
*/
void DynamicModel::addTileStates(int x, int y, double stack_height, bool valid) {

    /*if (valid) {
        this->flags[x][y] = RoomModel::OPEN;
    }
    else {
        this->flags[x][y] = RoomModel::CLOSED;
    }*/

    this->stack_height[x][y] += stack_height;
}
/*
    Returns an item at a given position, will return nullptr
    if no item was found, will include the item's affected tiles
    @param x coordinate
    @param y coordinate
    @return Item pointer
*/
Item *DynamicModel::getItemAtPosition(int x, int y) {
    return this->highest_items[x][y];
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

    if (!rotation_only) {
        Item *found_item = this->getItemAtPosition(item->x, item->y);

        if (found_item != nullptr) {
            if (found_item->getDefinition()->can_stack) {
                item->z = this->getStackHeight(item->x, item->y);// +(item->getDefinition()->can_stack ? 0.99 : 0);
            }
            else {
                item->z = this->room->getModel()->getSquareHeight(item->x, item->y);
            }
        }
        else {
            item->z = this->room->getModel()->getSquareHeight(item->x, item->y);
        }
    }

    item->updateEntities();
}

/*
    Deconstructor for DynamicModel
*/
DynamicModel::~DynamicModel() {

}

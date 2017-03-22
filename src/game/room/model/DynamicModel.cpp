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
    stack_height(Array2D<double>(0, 0)),
    tile_height(Array2D<double>(0, 0)) {

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

    this->stack_height = Array2D<double>(this->map_size_x, this->map_size_y);
    this->tile_height = Array2D<double>(this->map_size_x, this->map_size_y);

    for (int y = 0; y < map_size_y; y++) {
        for (int x = 0; x < map_size_x; x++) {

            int index = this->getSearchIndex(x, y);

            this->flags[x][y] = room->getModel()->squares[index];
            this->stack_height[x][y] = room->getModel()->square_height[index];
            this->tile_height[x][y] = room->getModel()->square_height[index];
            this->items[x][y] = nullptr;
        }
    }

    std::vector<Item*> items = this->room->getItems(FLOOR_ITEM);

    for (int i = 0; i < items.size(); i++) {

        Item *item = items.at(i);

        if (item == nullptr) {
            continue;
        }

        Item *existing_item = this->items[item->x][item->y];

        if (existing_item != nullptr) {
            if (existing_item->getDefinition()->interaction_type == "gate") {
                continue;
            }
        }
        else {

            this->items[item->x][item->y] = item;


            bool valid = false;

            if (item->getDefinition()->can_sit) {
                valid = true;
            }

            if (item->getDefinition()->interaction_type == "bed") {
                valid = true;
            }

            if (item->getDefinition()->is_walkable) {
                valid = true;
            }

            if (item->getDefinition()->interaction_type == "gate") {
                if (item->extra_data == "1") {
                    valid = true;
                }
                else {
                    valid = false;
                }
            }

            double stack_height = 0;

            if (item->getDefinition()->can_stack) {
                stack_height = item->getDefinition()->stack_height;
            }

            this->addTileStates(item->x, item->y, stack_height, valid);

            for (auto kvp : item->getAffectedTiles()) {

                Item *existing_item_affected = this->items[kvp.second.x][kvp.second.y];

                if (existing_item_affected != nullptr) {
                    if (existing_item_affected->getDefinition()->interaction_type == "gate") {
                        continue;
                    }
                }
                else {

                    this->items[kvp.second.x][kvp.second.y] = item;
                    this->addTileStates(kvp.second.x, kvp.second.y, stack_height, valid);
                }
            }
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
    }

    this->stack_height[x][y] =+ stack_height;
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


    this->handleItemAdjustment(item);
    this->regenerateCollisionMaps();

    this->room->getItems().push_back(item);
    this->room->send(PlaceItemMessageComposer(item));
    
    item->save();
}

/*
    Update the position, must be in a room!

    @return none
*/
void DynamicModel::updateItemPosition(Item *item, bool calculate_height) {

    if (calculate_height) {
        this->handleItemAdjustment(item);
    }

    this->room->getDynamicModel()->regenerateCollisionMaps();

    item->updateStatus();
    item->save();
}

/*
    Deal with the stacking of items and general affected tiles if the item was moved or placed

    @param Item to handle
    @return none
*/
void DynamicModel::handleItemAdjustment(Item *item) {
    
    if (item->isFloorItem()) {
        if (item->getDefinition()->can_stack) {
            std::cout << "can stack: " << item->id << ", " << item->getDefinition()->id << endl;
            item->z = this->getStackHeight(item->x, item->y);
        }
        else {
            item->z = this->getTileHeight(item->x, item->y);
        }
    }

    item->updateEntities();
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

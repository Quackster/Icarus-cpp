/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "dao/ItemDao.h"

#include "game/item/Item.h"
#include "game/player/Player.h"

#include "communication/outgoing/item/UpdateInventoryMessageComposer.h"
#include "communication/outgoing/item/InventoryMessageComposer.h"
#include "communication/outgoing/item/FurniListNotificationComposer.h"
#include "communication/outgoing/item/RemoveInventoryItemComposer.h"

#include "Inventory.h"

/*
    Constructor for Inventory

    @param list of inventory items
*/
Inventory::Inventory(Player *player, std::vector<Item*> items) :
    player(player),
    items(items) { }

/*
    Returns a list of items, by defined item type (such as only selecting wall or floor items)

    @param ItemType value
    @return list of items
*/
std::vector<Item*> Inventory::getItems(ItemType item_type) {

    std::vector<Item*> return_items;

    for (Item *item : this->items) {
        
        if (item_type == WALL_ITEM && item->isWallItem()) {
            return_items.push_back(item);
        }

        if (item_type == FLOOR_ITEM && item->isFloorItem()) {
            return_items.push_back(item);
        }

    }

    return return_items;
}

/*
    Insert an item to the inventory, this will also send a notification that a new item
    has been added

    @param Item instance
    @return none
*/
void Inventory::addItem(Item *item) {

    this->items.push_back(item);
    this->player->send(FurniListNotificationComposer(item->id, 1));
}

/*
    Remove the item from the player's inventory

    @param Item ptr
    @return none
*/
void Inventory::removeItem(Item *item, bool delete_from_database) {

    // Remove from vector
    this->items.erase(std::remove(this->items.begin(), this->items.end(), item), this->items.end());

    // Show client that the item is gone
    this->player->send(RemoveInventoryItemComposer(item->id));

    if (delete_from_database) {
        ItemDao::remove(item);
    }
    
}

/*
    Get Item by item id

    @param item id
    @return Item ptr instance
*/
Item *Inventory::getItem(int item_id) {

    for (Item *item : this->items) {
        if (item->id == item_id) {
            return item;
        }
    }

    return nullptr;
}

/*
    Force update inventory system

    @return none
*/
void Inventory::update() {

    player->send(UpdateInventoryMessageComposer());

    player->send(InventoryMessageComposer(
        player->getInventory()->getItems(FLOOR_ITEM),
        player->getInventory()->getItems(WALL_ITEM)));
}

/*
    Deconstructor for inventory
*/
Inventory::~Inventory() {

    for (Item *item : this->items) {
        delete item;
    }
}
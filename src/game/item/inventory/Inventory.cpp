/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "game/item/Item.h"
#include "game/player/Player.h"

#include "communication/outgoing/item/UpdateInventoryMessageComposer.h"
#include "communication/outgoing/item/InventoryMessageComposer.h"
#include "communication/outgoing/item/FurniListNotificationComposer.h"

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

void Inventory::addItem(Item *item) {

	this->items.push_back(item);

	player->send(FurniListNotificationComposer(item->id, 1));
}

Item *Inventory::getItem(int item_id) {

	for (Item *item : this->items) {
		if (item->id == item_id) {
			return item;
		}
	}

	return nullptr;
}

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
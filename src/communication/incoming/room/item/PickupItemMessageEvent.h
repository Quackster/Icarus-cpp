/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "communication/incoming/MessageEvent.h"

#include "game/item/Item.h"
#include "game/room/Room.h"

#include "game/item/inventory/Inventory.h"

class PickupItemMessageEvent : public MessageEvent {

public:
	PickupItemMessageEvent() { }

	void handle(Player *player, Request &request) {

		if (!player->getRoomUser()->in_room) {
			return;
		}

		int unknown = request.readInt();
		int item_id = request.readInt();

		Room *room = player->getRoomUser()->getRoom();
		Item *item = room->getItem(item_id);

		if (item == nullptr) {
			return;
		}

		bool can_pickup = false;

		if (room->hasRights(player)) {
			can_pickup = true;
		}

		if (item->owner_id == player->getDetails()->id) {
			can_pickup = true;
		}
		
		if (player->hasFuse("room_item_take")) {
			can_pickup = true;
		}

		if (!can_pickup) {
			return;
		}

		if (item->isFloorItem()) {
			item->x = -1;
			item->x = -1;
			item->updateEntities();
		}

		item->room_id = -1;
		item->user_id = player->getDetails()->id;
		item->save();

		room->removeItem(item);
		
		player->getInventory()->addItem(item);
		player->getInventory()->update();
	}
};
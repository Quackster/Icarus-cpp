/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "game/item/Item.h"

#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/room/entry/RoomSpacesMessageComposer.h"

#include "misc/Utilities.h"

class ApplyRoomDecoration : public MessageEvent {

public:
	ApplyRoomDecoration() { }

    void handle(Player *player, Request &request) { 
	
		if (!player->getRoomUser()->in_room) {
			return;
		}

		Room *room = player->getRoomUser()->getRoom();

		if (!room->hasRights(player)) {
			return;
		}

		Item *item = player->getInventory()->getItem(request.readInt());

		if (item == nullptr) {
			return;
		}

		if (Utilities::contains(item->getDefinition()->item_name, "a2")) {

			if (item->extra_data.length() > 0) {
				room->send(RoomSpacesMessageComposer("floor", item->extra_data));
				room->getData()->floor = item->extra_data;
			}
		}

		if (Utilities::contains(item->getDefinition()->item_name, "wallpaper")) {

			if (item->extra_data.length() > 0) {
				room->send(RoomSpacesMessageComposer("wallpaper", item->extra_data));
				room->getData()->wallpaper = item->extra_data;
			}
		}

		if (Utilities::contains(item->getDefinition()->item_name, "landscape")) {

			player->send(RoomSpacesMessageComposer("landscape", item->extra_data));
			room->getData()->outside = item->extra_data;

		}

		player->getInventory()->removeItem(item);

		room->save();
	}
};
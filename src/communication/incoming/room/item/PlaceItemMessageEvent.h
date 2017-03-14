/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "misc/Utilities.h"

#include "game/room/Room.h"
#include "game/item/Item.h"

#include "communication/incoming/MessageEvent.h"

#include "communication/outgoing/room/item/PlaceItemMessageComposer.h"

class PlaceItemMessageEvent : public MessageEvent {

public:
	PlaceItemMessageEvent() { }

	void handle(Player *player, Request &request) { 
	
		if (!player->getRoomUser()->in_room) {
			return;
		}

		Room *room = player->getRoomUser()->getRoom();

		if (!room->hasRights(player)) {
			return;
		}

		std::string input = request.readString();

		std::vector<std::string> data = Utilities::split(input, ' ');
		int item_id = stoi(Utilities::replaceChar(data[0], '-', ' '));

		Item *item = player->getInventory()->getItem(item_id);

		if (item == nullptr) {
			return;
		}

		if (item->isFloorItem()) {

			cout << input << endl;

			int x = stoi(data[1]);
			int y = stoi(data[2]);
			int rotation = stoi(data[3]);

			/*if (item.getData().getInteractionType() == InteractionType.ROLLER) {
				if (player.getRoomUser().getRoom().getItemManager().getItems(InteractionType.ROLLER).size() >= GameSettings.MAX_ROLLERS_PER_ROOM) {
					return; // todo: alert
				}
			}*/

			item->x = x;
			item->y = y;
			item->rotation = rotation;
			item->z = room->getModel()->getSquareHeight(item->x, item->y);
			
		}

		if (item->isWallItem()) {

			// :w=0,10 l=13,37 l
			
			std::vector<std::string> pos = Utilities::split(Utilities::split(input, ':')[1], ' ');

			char side;

			if (pos[2] == "l")
				side = 'l';
			else
				side = 'r';

			std::vector<std::string> x_data = Utilities::split(pos[0].substr(2), ',');

			item->width_x = stoi(x_data[0]);
			item->width_y = stoi(x_data[1]);

			std::vector<std::string> y_data = Utilities::split(pos[1].substr(2), ',');

			item->length_x = stoi(y_data[0]);
			item->length_y = stoi(y_data[1]);

			item->side = side;
		}

		item->room_id = room->id;
		item->save();

		player->getInventory()->removeItem(item, false);

		room->getItems().push_back(item);
		room->send(PlaceItemMessageComposer(item));
	}
};
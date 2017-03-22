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

class MoveItemMessageEvent : public MessageEvent {

public:
    MoveItemMessageEvent() { }

    void handle(Player *player, Request &request) {

        if (!player->getRoomUser()->in_room) {
            return;
        }

        Room *room = player->getRoomUser()->getRoom();

        if (!room->hasRights(player)) {
            return;
        }

        int item_id = request.readInt();

        Item *item = room->getItem(item_id);

        if (item == nullptr) {
            return;
        }

        bool rotation_only = false;

        if (item->isFloorItem()) {

            int x = request.readInt();
            int y = request.readInt();
            int rotation = request.readInt();

            if (x == item->x && item->y == y) {
                rotation_only = true;
            }

            item->x = x;
            item->y = y;
            item->rotation = rotation;
        } 
        
        if (item->isWallItem()) {
            std::string input = request.readString();
            std::vector<std::string> pos = Utilities::split(Utilities::split(input, ':')[1], ' ');
            item->parseWallPosition(pos[2] + "," + pos[0].substr(2) + " " + pos[1].substr(2));

        }
        
        room->getDynamicModel()->updateItemPosition(item, rotation_only);
    }
};
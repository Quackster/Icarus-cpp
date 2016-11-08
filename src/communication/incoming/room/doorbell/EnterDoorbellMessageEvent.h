/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "boot/Icarus.h"

#include "communication/outgoing/room/RoomDataMessageComposer.h"

#include "dao/RoomDao.h"

class EnterDoorbellMessageEvent : public MessageEvent {

public:
    EnterDoorbellMessageEvent() { }

    void handle(Player *player, Request &request) {

        int room_id = request.readInt();

        player->getRoomUser()->leaveRoom(false);

        Room *room = Icarus::getGame()->getRoomManager()->getRoom(room_id);

        if (room == nullptr) {

            room = RoomDao::getRoom(room_id);

            if (room != nullptr) {
                Icarus::getGame()->getRoomManager()->addRoom(room);
            }
            else {
                return;
            }
        }

        room->enter(player); // call method to finalise enter room
        player->send(RoomDataMessageComposer(room, player, true, false));
    }
};
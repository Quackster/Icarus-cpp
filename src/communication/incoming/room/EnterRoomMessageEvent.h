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


class EnterRoomMessageEvent : public MessageEvent {

public:
    EnterRoomMessageEvent() { }

    void handle(Player *player, Request &request) {

        int room_id = request.readInt();

        if (player->getRoomUser()->getRoom() != nullptr) {
            player->getRoomUser()->getRoom()->leave(player, false);// , !(player->getRoomUser()->getRoom()->getId() == room_id));
        }

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

    }
};
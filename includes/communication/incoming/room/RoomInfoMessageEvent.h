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

#include "communication/outgoing/room/RoomDataMessageComposer.h"

class RoomInfoMessageEvent : public MessageEvent {

public:
    RoomInfoMessageEvent() { }

    void handle(Player *player, Request &request) {

        int room_id = request.readInt();

        Room *room = Icarus::getGame()->getRoomManager()->getRoom(room_id);

        if (room == nullptr) {
            printf("room is null\n");
            return;
        }

        int i = request.readInt();
        int j = request.readInt();

        bool is_loading = i == 1;
        bool check_entry = j == 1;
        //printf("isloading: %i, chckentry: %i\n", i, j);

        player->send(RoomDataMessageComposer(room, player, is_loading, check_entry));
    }
};
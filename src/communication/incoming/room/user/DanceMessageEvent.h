/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "game/room/Room.h"

#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/room/user/DanceStatusMessageComposer.h"

class DanceMessageEvent : public MessageEvent {

public:
    DanceMessageEvent() { }

    void handle(Player *player, Request &request) {

        if (!player->getRoomUser()->inRoom()) {
            return;
        }

        RoomUser *room_user = player->getRoomUser();

        int dance_id = request.readInt();

        if (dance_id < 0 || dance_id > 4)
            dance_id = 0;

        room_user->setDanceId(dance_id);
        room_user->getRoom()->send(DanceStatusMessageComposer(room_user->getVirtualId(), dance_id));
    }
};
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

#include "communication/incoming/MessageEvent.h"

class ShowSignMessageEvent : public MessageEvent {

public:
    ShowSignMessageEvent() { }

    void handle(Player *player, Request &request) {

        if (!player->getRoomUser()->inRoom()) {
            return;
        }

        int sign_id = request.readInt();

        if (sign_id > 17) {
            return;
        }

        RoomUser *room_user = player->getRoomUser();

        room_user->setStatus("sign", std::to_string(sign_id));
        room_user->setSignTime(Icarus::getUnixTimestamp() + 5);
        room_user->updateStatus();
    }
};
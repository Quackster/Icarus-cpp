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

class ChatMessageEvent : public MessageEvent {

public:
    ChatMessageEvent() { }

    void handle(Player *player, Request &request) {

        if (!player->getRoomUser()->inRoom()) {
            return;
        }

        RoomUser *room_user = player->getRoomUser();
        room_user->awake();

        std::string message = request.readString();
        int bubble = request.readInt();
        int count = request.readInt();


        player->getRoomUser()->chat(message, bubble, count, false, true);
    }
};
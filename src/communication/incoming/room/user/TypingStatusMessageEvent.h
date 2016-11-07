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

#include "communication/headers/Incoming.h"

#include "communication/outgoing/room/user/TypingStatusMessageComposer.h"
#include "communication/incoming/MessageEvent.h"

class TypingStatusMessageEvent : public MessageEvent {

public:
    TypingStatusMessageEvent() { }

    void handle(Player *player, Request &request) {

        RoomUser *room_user = player->getRoomUser();

        if (!room_user->inRoom()) {
            return;
        }

        //std::cout << "Is typing: " << (request.getMessageId() == Incoming::StartTypingMessageEvent ? "true" : "false") << std::endl;

        room_user->getRoom()->send(TypingStatusMessageComposer(room_user->getVirtualId(), request.getMessageId() == Incoming::StartTypingMessageEvent));
    }
};
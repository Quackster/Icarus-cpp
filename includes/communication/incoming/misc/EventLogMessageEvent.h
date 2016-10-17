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

class EventLogMessageEvent : public MessageEvent {

public:
    EventLogMessageEvent() { }

    void handle(Player *player, Request &request) {

        if (!player->getNetworkConnection()->isNavigatorSent()) {
            Icarus::getMessageHandler()->invoke(Incoming::NewNavigatorMessageEvent, request, player);
        }

        if (!player->getNetworkConnection()->isUserInfoSent()) {
            Icarus::getMessageHandler()->invoke(Incoming::UserDataMessageEvent, request, player);
        }
    }
};
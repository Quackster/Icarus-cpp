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
#include "communication/outgoing/login/AuthenticateMessageComposer.h"

#include "dao/UserDao.h"

class VersionCheckMessageEvent : public MessageEvent {

public:
    VersionCheckMessageEvent() { }

    void handle(Player *player, Request &request) {

        std::string revision = request.readString();

        if (revision == Icarus::getGameConfiguration()->getString("game.revision")) {
            return;
        }

        // Kick user if they're using incorrect swfs
        player->getNetworkConnection()->getSocket().close();
    }
};
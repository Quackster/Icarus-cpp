/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "dao/MessengerDao.h"
#include "communication/incoming/MessageEvent.h"

class MessengerDeclineMessageEvent : public MessageEvent {

public:
    MessengerDeclineMessageEvent() { }

    void handle(Player *player, Request &request) {

        bool delete_all = request.readBool();

        if (delete_all) {

            for (auto kvp : *player->getMessenger()->getRequests()) {
                MessengerDao::removeRequest(kvp.first, player->getDetails()->getId());
            }

            player->getMessenger()->clearRequests();
        }
        else {

            request.readInt();
            int from_id = request.readInt();

            MessengerDao::removeRequest(from_id, player->getDetails()->getId());
        }

    }
};
/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "game/messenger/MessengerUser.h"

#include "dao/UserDao.h"
#include "dao/MessengerDao.h"

#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/messenger/MessengerSendRequestComposer.h"

class MessengerRequestMessageEvent : public MessageEvent {

public:
    MessengerRequestMessageEvent() { }

    void handle(Player *player, Request &request) {

        std::string username = request.readString();
    
        if (username.length() < 0) {
            return;
        }

        int user_id = UserDao::getIdByUsername(username);

        if (user_id < 1) {
            return;
        }

        if (player->getMessenger()->hasRequest(user_id)) {
            return;
        }

        if (MessengerDao::newRequest(player->getDetails()->id, user_id)) {

            MessengerUser *user = new MessengerUser(user_id);
            player->getMessenger()->getRequests()->insert(std::make_pair(user_id, user));

            if (user->isOnline()) {
                user->getPlayer()->send(MessengerSendRequestComposer(player->getDetails()));
            }
        }
    }
};
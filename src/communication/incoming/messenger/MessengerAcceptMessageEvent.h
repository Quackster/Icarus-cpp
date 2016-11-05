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
#include "game/entities/EntityDetails.h"

#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/messenger/MessengerUpdateMessageComposer.h"

class MessengerAcceptMessageEvent : public MessageEvent {

public:
    MessengerAcceptMessageEvent() { }

    void handle(Player *player, Request &request) {

        int amount = request.readInt();

        for (int i = 0; i < amount; i++) {

            int to_id = player->getDetails()->id;
            int from_id = request.readInt();

            MessengerDao::removeRequest(from_id, to_id);
            MessengerDao::removeRequest(to_id, from_id);

            MessengerDao::newFriend(to_id, from_id);

            MessengerUser *user = new MessengerUser(from_id);
            player->getMessenger()->getFriends().insert(std::make_pair(from_id, user));

            if (user->isOnline()) {

                MessengerUser *to = new MessengerUser(to_id);

                user->getPlayer()->getMessenger()->getFriends().insert(std::make_pair(to_id, to));
                user->getPlayer()->send(MessengerUpdateMessageComposer(to, false));
            }

            player->send(MessengerUpdateMessageComposer(user, false));
        }


    }
};
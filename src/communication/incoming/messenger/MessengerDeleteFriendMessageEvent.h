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

#include "dao/MessengerDao.h"

#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/messenger/RemoveFriendMessageComposer.h"

class MessengerDeleteFriendMessageEvent: public MessageEvent{

public:
    MessengerDeleteFriendMessageEvent() { }

    void handle(Player *player, Request &request) {

        int amount = request.readInt();

        for (int i = 0; i < amount; i++) {

            int friend_id = request.readInt();

            if (player->getMessenger()->isFriend(friend_id)) {

                MessengerUser *user = player->getMessenger()->getFriend(friend_id);

                if (user->isOnline()) {
                    user->getPlayer()->getMessenger()->removeFriend(player->getDetails()->getId());
                    user->getPlayer()->send(RemoveFriendMessageComposer(player->getDetails()->getId()));
                }

                player->getMessenger()->removeFriend(friend_id);
                player->send(RemoveFriendMessageComposer(friend_id));

                MessengerDao::removeFriend(friend_id, player->getDetails()->getId());
            }
        }
    }
};
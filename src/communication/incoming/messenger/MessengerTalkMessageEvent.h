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
#include "communication/incoming/MessageEvent.h"

#include "dao/MessengerDao.h"

#include "communication/outgoing/messenger/MessengerMessageComposer.h"

class MessengerTalkMessageEvent : public MessageEvent {

public:
    MessengerTalkMessageEvent() { }

    void handle(Player *player, Request &request) {

        int friend_id = request.readInt();

        if (!player->getMessenger()->isFriend(friend_id)) {
            return;
        }

        MessengerUser *user = player->getMessenger()->getFriend(friend_id);
        std::string message = request.readString();

        if (message.length() < 1) {
            return;
        }

        MessengerDao::offlineMessage(friend_id, player->getDetails()->id, message, !user->isOnline());

        if (user->isOnline()) {
            user->getPlayer()->send(MessengerMessageComposer(player->getDetails()->id, message));
        }
    }
};
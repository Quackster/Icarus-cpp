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

#include "communication/outgoing/messenger/MessengerMessageComposer.h"
#include "communication/outgoing/messenger/MessengerCategoriesMessageComposer.h"
#include "communication/outgoing/messenger/FriendsListMessageComposer.h"
#include "communication/outgoing/messenger/MessengerRequestsMessageComposer.h"

class MessengerInitMessageEvent : public MessageEvent {

public:
    MessengerInitMessageEvent() { }

    void handle(Player *player, Request &request) {
        
        if (player->getMessenger() == nullptr) {
            return;
        }

        player->send(MessengerCategoriesMessageComposer());
        player->send(FriendsListMessageComposer(player->getMessenger()->getFriends()));
        player->send(MessengerRequestsMessageComposer(player->getDetails(), player->getMessenger()->getRequests()));

        std::map<std::string, int> offline_messages = MessengerDao::getOfflineMessages(player->getDetails()->id);

        if (offline_messages.size() > 0) {
            for (auto kvp : offline_messages) {
                player->send(MessengerMessageComposer(kvp.second, kvp.first));
            }
        }

		MessengerDao::readMessages(player->getDetails()->id);

		player->getMessenger()->initialised = true;
		player->getMessenger()->sendStatus(false);
    }
};
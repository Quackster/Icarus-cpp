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
#include "misc/Utilities.h"

#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/messenger/MessageInviteMessageComposer.h"

class MessengerInviteMessageEvent : public MessageEvent {

public:
    MessengerInviteMessageEvent() { }

    void handle(Player *player, Request &request) {

        std::vector<int> friends;

        int friend_count = request.readInt();

        if (friend_count == 0) {
            return;
        }

        for (int i = 0; i < friend_count; i++) {

            int friend_id = request.readInt();

            if (Icarus::getPlayerManager()->getPlayerById(friend_id) != nullptr) {
                if (player->getMessenger()->isFriend(friend_id)) {
                    friends.push_back(friend_id);
                }
            }
        }

        std::string invite_message = request.readString();
        invite_message = Utilities::escape(invite_message, true);

        MessageInviteMessageComposer message_compose = MessageInviteMessageComposer(player->getDetails()->id, invite_message);

        for (int friend_id : friends) {
            
            MessengerUser *messenger_user = player->getMessenger()->getFriend(friend_id);

            if (messenger_user->isOnline()) {
                messenger_user->getPlayer()->send(message_compose);
            }
        }
    }
};
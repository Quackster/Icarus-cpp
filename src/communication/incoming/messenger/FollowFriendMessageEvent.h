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

#include "game/messenger/MessengerUser.h"
#include "communication/incoming/MessageEvent.h"

#include "communication/outgoing/messenger/FollowFriendMessageComposer.h"
#include "communication/outgoing/messenger/FollowErrorMessageComposer.h"

class FollowFriendMessageEvent : public MessageEvent {

public:
    FollowFriendMessageEvent() { }

    void handle(Player *player, Request &request) {

        int friend_id = request.readInt();
        int error_id = -1;

        if (!player->getMessenger()->isFriend(friend_id)) {
            return;
        }

        MessengerUser *client = player->getMessenger()->getFriend(friend_id);

        if (client->isOnline()) {
            if (client->getPlayer()->getRoomUser()->in_room) {
                player->send(FollowFriendMessageComposer(client->getPlayer()->getRoomUser()->getRoom()->id));
            } 
            else {
                error_id = 2; // User is not in a room
            }

        } 
        else {
            error_id = 1; // User is offline

        }
        
        if (error_id != -1) {
            player->send(FollowErrorMessageComposer(error_id));
        }
    }
};
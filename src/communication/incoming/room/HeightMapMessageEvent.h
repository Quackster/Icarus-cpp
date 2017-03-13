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

#include "communication/incoming/MessageEvent.h"

#include "communication/outgoing/room/model/FloorMapMessageComposer.h"
#include "communication/outgoing/room/model/HeightMapMessageComposer.h"

#include "communication/outgoing/room/RoomDataMessageComposer.h"
#include "communication/outgoing/room/entry/RoomOwnerRightsComposer.h"

#include "communication/outgoing/room/user/UserDisplayMessageComposer.h"
#include "communication/outgoing/room/user/UserStatusMessageComposer.h"
#include "communication/outgoing/room/user/DanceStatusMessageComposer.h"
#include "communication/outgoing/room/user/IdleStatusMessageComposer.h"

class HeightMapMessageEvent : public MessageEvent {

public:
    HeightMapMessageEvent() { }

    void handle(Player *player, Request &request) {

        Room *room = player->getRoomUser()->getRoom();

        if (room == nullptr) {
            return;
        }       
       
        player->getRoomUser()->in_room = true;
        player->getRoomUser()->is_loading_room = false;

        player->send(HeightMapMessageComposer(room));
        player->send(FloorMapMessageComposer(room));

        player->send(UserDisplayMessageComposer(room->getEntities()));
        player->send(UserStatusMessageComposer(room->getEntities()));
        player->send(RoomDataMessageComposer(room, player, true, true));
        player->send(RoomOwnerRightsComposer(room->getData()->id, room->hasRights(player, true)));

        // Tell friends we're in a room! :)
        player->getMessenger()->sendStatus(false);



        // Show anyone dancing
        for (auto kvp : room->getEntities()) {

            Entity *entity = kvp.second;
            RoomUser *room_user = entity->getRoomUser();

            if (room_user->dance_id > 0) {
                player->send(DanceStatusMessageComposer(room_user->virtual_id, room_user->dance_id));
            }

            if (room_user->is_asleep) {
                player->send(IdleStatusMessageComposer(room_user->virtual_id, true));
            }
        }
    }
};
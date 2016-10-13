/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "communication/incoming/MessageEvent.h"

#include "communication/outgoing/room/model/FloorMapMessageComposer.h"
#include "communication/outgoing/room/model/HeightMapMessageComposer.h"

#include "communication/outgoing/room/RoomDataMessageComposer.h"        

class HeightMapMessageEvent : public MessageEvent {

public:
    HeightMapMessageEvent() { }

    void handle(Player *player, Request &request) {

        Room *room = player->getRoomUser()->getRoom();

        if (room == nullptr) {
            return;
        }

        player->send(HeightMapMessageComposer(room));
        player->send(FloorMapMessageComposer(room));

        room->enter(player); // call method to finalise enter room

        player->send(RoomDataMessageComposer(room, player, 1, 1));

        Response res(Outgoing::RoomOwnerRightsComposer);
        res.writeInt(room->getData()->getId());
        res.writeBool(false);
        player->getNetworkConnection()->send(res);
    }
};
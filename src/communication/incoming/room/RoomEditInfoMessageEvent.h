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

#include "communication/outgoing/room/RoomSettingsDataMessageComposer.h"

class RoomEditInfoMessageEvent : public MessageEvent {

public:
    RoomEditInfoMessageEvent() { }

    void handle(Player *player, Request &request) {

        if (!player->getRoomUser()->in_room) {
            return;
        }

        Room *room = player->getRoomUser()->getRoom();

        if (!room->hasRights(player->getDetails()->id, true)) {
            return;
        }

        player->send(RoomSettingsDataMessageComposer(room));
    }
};
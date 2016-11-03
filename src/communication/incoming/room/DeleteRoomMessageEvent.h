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
#include "dao/RoomDao.h"

class DeleteRoomMessageEvent : public MessageEvent {

public:
    DeleteRoomMessageEvent() { }

    void handle(Player *player, Request &request) {

        if (!player->getRoomUser()->inRoom()) {
            return;
        }

        Room *room = player->getRoomUser()->getRoom();

        if (!room->hasRights(player->getDetails()->getId(), true)) {
            return;
        }

        room->kickPlayers();

        // TODO: Put furniture back into peoples inventories

        // Delete room from database
        RoomDao::deleteRoom(room->getId());

        // Delete room information
        room->dispose(true);
    }
};
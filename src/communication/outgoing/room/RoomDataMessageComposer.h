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
#include "game/player/Player.h"

#include "communication/outgoing/MessageComposer.h"

class RoomDataMessageComposer : public MessageComposer {

public:
    RoomDataMessageComposer(Room *room, Player *player, bool is_loading, bool check_entry) {

        this->room = room;
        this->player = player;
        this->is_loading = is_loading;
        this->check_entry = check_entry;

		std::cout << " Room data rec" << (is_loading ? "t" : "f") << ", " << check_entry << std::endl;
    }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeBool(this->is_loading);
        room->serialise(response, true);
        response.writeBool(this->check_entry);
        response.writeBool(false);
        response.writeBool(false);
        response.writeBool(false);
        response.writeInt(room->getData()->getWhoCanMute());
        response.writeInt(room->getData()->getWhoCanKick());
        response.writeInt(room->getData()->getWhoCanBan());
        response.writeBool(room->hasRights(player->getDetails()->getId(), true)); // TODO: Rights, true if moderator or room owner
        response.writeInt(0);
        response.writeInt(0);
        response.writeInt(0);
        response.writeInt(0);
        response.writeInt(0);
        return response;
    }

    const int getHeader() const {
        return Outgoing::RoomDataMessageComposer;
    }

private:
    Room *room;
    Player *player;
    bool is_loading;
    bool check_entry;

};
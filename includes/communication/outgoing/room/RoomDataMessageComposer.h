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
    }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeBool(this->is_loading);
        
        response.writeInt(room->getData()->getId());
        response.writeString(room->getData()->getName());
        response.writeInt(room->getData()->getOwnerId());
        response.writeString(room->getData()->getOwnerName()); // Owner name
        response.writeInt(room->getData()->getState());
        response.writeInt(room->getPlayers().size()); // Users now
        response.writeInt(room->getData()->getUsersMax());
        response.writeString(room->getData()->getDescription());
        response.writeInt(room->getData()->getTradeState());
        response.writeInt(room->getData()->getScore());
        response.writeInt(0);
        response.writeInt(room->getData()->getCategory());
        response.writeInt(room->getData()->getTags().size());

        for (std::string tag : room->getData()->getTags()) {
            response.writeString(tag);
        }

        response.writeInt(56);

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
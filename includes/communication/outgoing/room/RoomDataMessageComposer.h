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

    Response compose() {
        Response response = this->createResponse();
        response.writeBool(this->is_loading);
        room->serialise(response, is_loading);
        response.writeBool(this->check_entry);
        response.writeBool(false);
        response.writeBool(false);
        response.writeBool(false);
        response.writeInt(room->getData()->getWhoCanMute());
        response.writeInt(room->getData()->getWhoCanKick());
        response.writeInt(room->getData()->getWhoCanBan());
        response.writeBool(false); // TODO: Rights, true if moderator or room owner
        response.writeInt(0);
        response.writeInt(0);
        response.writeInt(0);
        response.writeInt(0);
        response.writeInt(0);
        return response;
    }

    int getHeader() {
        return Outgoing::RoomDataMessageComposer;
    }

private:
    Room *room;
    Player *player;
    bool is_loading;
    bool check_entry;

};
#pragma once
#include "communication/incoming/MessageEvent.h"

#include "communication/outgoing/room/RoomDataMessageComposer.h"

class RoomInfoMessageEvent : public MessageEvent {

public:
    RoomInfoMessageEvent() { }

    void handle(Player *player, Request &request) {

        int room_id = request.readInt();

        Room *room = Icarus::getGame()->getRoomManager()->getRoom(room_id);

        if (room == nullptr) {
            return;
        }

        bool is_loading = request.readInt() == 1;
        bool check_entry = request.readInt() == 1;

        player->send(RoomDataMessageComposer(room, player, is_loading, check_entry));
    }
};
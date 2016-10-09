#pragma once
#include "communication/incoming/MessageEvent.h"

#include "communication/outgoing/room/RoomDataMessageComposer.h"

class RoomInfoMessageEvent : public MessageEvent {

public:
    RoomInfoMessageEvent() { }

    void handle(Player *player, Request &request) {

        //request.readInt();
        int room_id = request.readInt();

        std::cout << "Roomid: " << room_id << std::endl;

        Room *room = Icarus::getGame()->getRoomManager()->getRoom(room_id);

        if (room == nullptr) {
            //return;
        }

        int is_loading = request.readInt();
        int check_entry = request.readInt();

        std::cout << " Room request: " << is_loading << " - " << check_entry << std::endl;

        player->send(RoomDataMessageComposer(room, player, is_loading, check_entry));
        //

    }
};
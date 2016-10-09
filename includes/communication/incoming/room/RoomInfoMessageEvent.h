#pragma once
#include "communication/incoming/MessageEvent.h"

#include "communication/outgoing/room/RoomDataMessageComposer.h"

class RoomInfoMessageEvent : public MessageEvent {

public:
    RoomInfoMessageEvent() { }

    void handle(Player *player, Request request) {

        //request.readInt();
        int room_id = request.readInt();

        std::cout << "Roomid: " << room_id << std::endl;

        Room *room = Icarus::getGame()->getRoomManager()->getRoom(room_id);

        if (room == nullptr) {
            //return;
        }

        bool is_loading = request.readInt() == 1;
        bool check_entry = request.readInt() == 1;

        //player->send(RoomDataMessageComposer(room, player, check_entry, is_loading));
        //std::cout << " Room request: " << room_id << std::endl;

    }
};
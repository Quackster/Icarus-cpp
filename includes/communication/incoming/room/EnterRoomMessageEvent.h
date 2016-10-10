#pragma once
#include "communication/incoming/MessageEvent.h"

class EnterRoomMessageEvent : public MessageEvent {

public:
    EnterRoomMessageEvent() { }

    void handle(Player *player, Request &request) {

        int room_id = request.readInt();

        Room *room = Icarus::getGame()->getRoomManager()->getRoom(room_id);

        if (room == nullptr) {
            return;
        }



    }
};
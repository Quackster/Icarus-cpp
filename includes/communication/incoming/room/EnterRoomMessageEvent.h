#pragma once
#include "communication/incoming/MessageEvent.h"

class EnterRoomMessageEvent : public MessageEvent {

public:
    EnterRoomMessageEvent() { }

    void handle(Player *player, Request request) {

        int room_id = request.readInt();

        std::cout << " Room request: " << room_id << std::endl;

    }
};
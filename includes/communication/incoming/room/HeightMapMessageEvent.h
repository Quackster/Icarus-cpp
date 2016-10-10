#pragma once
#include "communication/incoming/MessageEvent.h"

#include "communication/outgoing/room/RoomDataMessageComposer.h"

class HeightMapMessageEvent : public MessageEvent {

public:
    HeightMapMessageEvent() { }

    void handle(Player *player, Request &request) {


    }
};
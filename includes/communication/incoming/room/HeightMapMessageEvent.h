#pragma once
#include "communication/incoming/MessageEvent.h"

#include "communication/outgoing/room/model/FloorMapMessageComposer.h"
#include "communication/outgoing/room/model/HeightMapMessageComposer.h"

class HeightMapMessageEvent : public MessageEvent {

public:
    HeightMapMessageEvent() { }

    void handle(Player *player, Request &request) {

        player->send(HeightMapMessageComposer(player->getRoomUser()->getRoom()));
        player->send(FloorMapMessageComposer(player->getRoomUser()->getRoom()));
        

    }
};
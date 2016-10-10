#pragma once
#include "communication/incoming/MessageEvent.h"

class WalkMessageEvent : public MessageEvent {

public:
    WalkMessageEvent() { }

    void handle(Player *player, Request &request) {



    }
};
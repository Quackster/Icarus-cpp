#pragma once
#include "game/player/Player.h"
#include "communication/headers/Outgoing.h"

#include "communication/streams/Request.h"
#include "communication/streams/Response.h"

class MessageEvent
{

public:
    virtual ~MessageEvent() {}
    virtual void handle(Player *player, Request &request) = 0;
};
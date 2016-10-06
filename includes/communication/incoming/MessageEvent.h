#pragma once
#include "game/session/Session.h"
#include "communication/headers/Outgoing.h"

#include "communication/streams/Request.h"
#include "communication/streams/Response.h"

class MessageEvent
{

public:
    virtual ~MessageEvent() {}
    virtual void handle(Session *session, Request request) = 0;
};
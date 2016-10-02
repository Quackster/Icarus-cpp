#pragma once
#include "managers/session/Session.h"
#include "headers/Outgoing.h"

#include "communication/streams/Request.h"
#include "communication/streams/Response.h"

class MessageEvent
{

public:
    virtual ~MessageEvent() {}
    virtual void handle(Session *session, Request request) = 0;
};
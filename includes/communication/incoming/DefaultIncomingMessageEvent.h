#pragma once
#include "communication/incoming/MessageEvent.h"

class DefaultIncomingMessageEvent : public MessageEvent {

public:
    DefaultIncomingMessageEvent() { }

    void handle(Session *session, Request request) {



    }
};
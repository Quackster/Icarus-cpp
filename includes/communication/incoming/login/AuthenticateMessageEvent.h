#pragma once
#include "communication/messages/IncomingMessage.h"

class AuthenticateMessageEvent : public IncomingMessage {

public:
    void read(Request request) {
        
    }

    int getHeader() {
        return Incoming::AuthenticateMessageEvent;
    }

};
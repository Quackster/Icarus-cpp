#pragma once
#include "communication/outgoing/MessageComposer.h"

class AuthenticateMessageComposer : public MessageComposer {

public:

    AuthenticateMessageComposer() { }

    Response compose() {
        Response response = this->createResponse();
        return response;
    }

    int getHeader() {
        return Outgoing::AuthenticationOKMessageComposer;
    }

};
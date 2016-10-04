#pragma once
#include "communication/outgoing/MessageComposer.h"

class DefaultComposer : public MessageComposer {

public:
    DefaultComposer() { }

    Response compose() {
        Response response = this->createResponse();
        return response;
    }

    int getHeader() {
        return Outgoing::AuthenticationOKMessageComposer;
    }
};
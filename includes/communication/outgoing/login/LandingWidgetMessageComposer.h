#pragma once
#include "communication/outgoing/MessageComposer.h"

class LandingWidgetMessageComposer : public MessageComposer {

public:
    LandingWidgetMessageComposer() { }

    Response compose() {
        Response response = this->createResponse();
        response.writeInt(0);
        return response;
    }

    int getHeader() {
        return Outgoing::LandingWidgetMessageComposer;
    }
};
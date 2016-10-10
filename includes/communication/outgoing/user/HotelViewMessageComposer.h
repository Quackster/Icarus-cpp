#pragma once
#include <string>

#include "communication/outgoing/MessageComposer.h"

class HotelViewMessageComposer : public MessageComposer {

public:
    HotelViewMessageComposer() { }

    Response compose() {
        Response response = this->createResponse();;
        return response;
    }

    int getHeader() {
        return Outgoing::HotelScreenMessageComposer;
    }


};
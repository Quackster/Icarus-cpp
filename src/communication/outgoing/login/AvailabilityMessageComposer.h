/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "communication/outgoing/MessageComposer.h"

class AvailabilityMessageComposer : public MessageComposer {

public:
    AvailabilityMessageComposer() { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeBool(true);
        response.writeBool(false);
        response.writeBool(true);
        return response;
    }

    const int getHeader() const {
        return -1234;// return Outgoing::AvailabilityMessageComposer;
    }
};
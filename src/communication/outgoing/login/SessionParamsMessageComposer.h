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

class SessionParamsMessageComposer : public MessageComposer {

public:
    SessionParamsMessageComposer() { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(9);
        response.writeInt(0);
        response.writeInt(0);
        response.writeInt(1);
        response.writeInt(1);
        response.writeInt(3);
        response.writeInt(0);
        response.writeInt(2);
        response.writeInt(1);
        response.writeInt(4);
        response.writeInt(0);
        response.writeInt(5);
        response.writeString("dd-MM-yyyy");
        response.writeInt(7);
        response.writeBool(false);
        response.writeInt(8);
        response.writeString("hotel-co.uk");
        response.writeInt(9);
        response.writeBool(false);
        return response;
    }

    const int getHeader() const {
        return Outgoing::SessionParamsMessageComposer;
    }
};
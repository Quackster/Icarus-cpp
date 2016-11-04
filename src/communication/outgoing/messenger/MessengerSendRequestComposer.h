/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <string>

#include "communication/outgoing/MessageComposer.h"

class MessengerSendRequestComposer : public MessageComposer {

public:
    MessengerSendRequestComposer(EntityDetails *details) :
        details(details) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->details->id);
        response.writeString(this->details->username);
        response.writeString(this->details->figure);
        return response;
    }

    const int getHeader() const {
        return Outgoing::MessengerSendRequest;
    }

private:
    EntityDetails *details;
};
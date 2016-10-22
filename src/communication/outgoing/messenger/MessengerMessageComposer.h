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

class MessengerMessageComposer : public MessageComposer {

public:
    MessengerMessageComposer(int from_id, std::string message) :
        from_id(from_id),
        message(message) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(from_id);
        response.writeString(message);
        response.writeInt(0);
        return response;
    }

    const int getHeader() const {
        return Outgoing::MessengerMessageComposer;
    }

private:
    int from_id;
    std::string message;
};
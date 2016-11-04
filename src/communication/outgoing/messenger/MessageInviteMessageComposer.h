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

class MessageInviteMessageComposer : public MessageComposer {

public:
    MessageInviteMessageComposer(int user_id, std::string message) :
        user_id(user_id),
        message(message) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->user_id);
        response.writeString(this->message);
        return response;
    }

    const int getHeader() const {
        return Outgoing::MessageInviteMessageComposer;
    }

public:
    int user_id;
    std::string message;
};
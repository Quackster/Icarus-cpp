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

class GenericDoorbellMessageComposer : public MessageComposer {

public:
    GenericDoorbellMessageComposer(int notify_code) :
        notify_code(notify_code) { }

    GenericDoorbellMessageComposer(std::string username) :
        username(username) { }

    const Response compose() const {
        Response response = this->createResponse();

        if (this->notify_code != -9001) {
            response.writeInt(this->notify_code);
        }
        else {
            response.writeString(this->username);
        }

        return response;
    }

    const int getHeader() const {
        return Outgoing::GenericDoorbellMessageComposer;
    }

private:
    int notify_code = -9001;
    std::string username;
};
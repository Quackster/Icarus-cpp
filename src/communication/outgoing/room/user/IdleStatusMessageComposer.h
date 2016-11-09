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

class IdleStatusMessageComposer : public MessageComposer {

public:
    IdleStatusMessageComposer(int virtual_id, bool asleep) :
        virtual_id(virtual_id),
        asleep(asleep) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->virtual_id);
        response.writeBool(this->asleep);
        return response;
    }

    const int getHeader() const {
        return Outgoing::IdleStatusMessageComposer;
    }

private:
    int virtual_id;
    bool asleep;
};
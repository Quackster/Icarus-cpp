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

class DanceStatusMessageComposer : public MessageComposer {

public:
    DanceStatusMessageComposer(int virtual_id, int dance_id) :
        virtual_id(virtual_id),
        dance_id(dance_id) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->virtual_id);
        response.writeInt(this->dance_id);
        return response;
    }

    const int getHeader() const {
        return Outgoing::DanceStatusMessageComposer;
    }

private:
    int virtual_id;
    int dance_id;
};
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

class RemoveUserMessageComposer : public MessageComposer {

public:
    RemoveUserMessageComposer(int virtual_id) : 
        virtual_id(virtual_id) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeString(std::to_string(this->virtual_id));
        return response;
    }

    const int getHeader() const {
        return Outgoing::RemoveUserMessageComposer;
    }

private:
    int virtual_id;
};
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

class TypingStatusMessageComposer : public MessageComposer {

public:
    TypingStatusMessageComposer(int virtual_id, bool is_typing) :
        virtual_id(virtual_id),
        is_typing(is_typing) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->virtual_id);
        response.writeInt(this->is_typing);
        return response;
    }

    const int getHeader() const {
        return Outgoing::TypingStatusMessageComposer;
    }

private:
    int virtual_id;
    bool is_typing;
};
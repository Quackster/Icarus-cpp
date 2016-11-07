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

class TalkMessageComposer : public MessageComposer {

public:
    TalkMessageComposer(int virtual_id, bool shout, std::string message, int count, int text_colour) :
        virtual_id(virtual_id),
        shout(shout),
        message(message),
        count(count),
        text_colour(text_colour) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->virtual_id);
        response.writeString(this->message);
        response.writeInt(0);
        response.writeInt(this->text_colour);
        response.writeInt(0);
        response.writeInt(this->count);
        return response;
    }

    const int getHeader() const {
        return shout ? Outgoing::ShoutMessageComposer : Outgoing::ChatMessageComposer;
    }

private:
    int virtual_id;
    bool shout;
    std::string message;
    int count;
    int text_colour;
};
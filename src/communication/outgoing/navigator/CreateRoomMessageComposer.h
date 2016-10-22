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

class CreateRoomMessageComposer : public MessageComposer {

public:
    CreateRoomMessageComposer(int room_id, std::string room_name) :
        room_id(room_id),
        room_name(room_name) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->room_id);
        response.writeString(this->room_name);
        return response;
    }

    const int getHeader() const {
        return Outgoing::CreateRoomMessageComposer;
    }

private:
    int room_id;
    std::string room_name;
};
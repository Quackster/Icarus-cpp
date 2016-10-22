/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "game/room/Room.h"
#include "game/player/Player.h"

#include "communication/outgoing/MessageComposer.h"

class RoomSpacesMessageComposer : public MessageComposer {

public:
    RoomSpacesMessageComposer(std::string space, std::string data)
        : space(space), data(data) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeString(this->space);
        response.writeString(this->data);
        return response;
    }

    const int getHeader() const {
        return Outgoing::RoomSpacesMessageComposer;
    }

private:
    std::string space;
    std::string data;
};
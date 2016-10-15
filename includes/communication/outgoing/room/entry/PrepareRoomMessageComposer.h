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

class PrepareRoomMessageComposer : public MessageComposer {

public:
    PrepareRoomMessageComposer(int room_id) : 
        room_id(room_id) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->room_id);
        return response;
    }

    const int getHeader() const {
        return Outgoing::RoomUpdateMessageComposer;
    }

private:
    int room_id;
};
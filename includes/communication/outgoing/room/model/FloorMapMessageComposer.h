/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "boot/Icarus.h"
#include "game/room/model/RoomModel.h"

#include "game/room/Room.h"
#include "game/player/Player.h"

#include "communication/outgoing/MessageComposer.h"

class FloorMapMessageComposer : public MessageComposer {

public:
    FloorMapMessageComposer(Room *room) : room(room) { }

    const Response compose() const {

        RoomModel *model = room->getModel();

        Response response = this->createResponse();
        response.writeBool(true);
        response.writeInt(room->getData()->getWallHeight());
        response.writeString(model->getFloorMap());

        return response;
    }

    const int getHeader() const {
        return Outgoing::FloorMapMessageComposer;
    }

private:
    Room *room;

};
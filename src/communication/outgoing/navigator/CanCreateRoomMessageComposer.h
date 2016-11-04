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

#include "communication/outgoing/MessageComposer.h"

class CanCreateRoomMessageComposer : public MessageComposer {

public:

    CanCreateRoomMessageComposer(Player *player) : 
        player(player) { }

    const Response compose() const {

        Response response = this->createResponse();
        response.writeInt(player->getRooms().size() >= Icarus::getGame()->MAX_ROOMS_PER_ACCOUNT ? 1 : 0);
        response.writeInt(Icarus::getGame()->MAX_ROOMS_PER_ACCOUNT);
        return response;
    }

    const int getHeader() const {
        return Outgoing::CanCreateRoomMessageComposer;
    }

private:
    Player *player;
};
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

#include "game/player/Player.h"
#include "communication/outgoing/MessageComposer.h"

class UserObjectMessageComposer : public MessageComposer {

public:
    UserObjectMessageComposer(Player *player) : player(player) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(player->getDetails()->id);
        response.writeString(player->getDetails()->username);
        response.writeString(player->getDetails()->figure);
        response.writeString("M");
        response.writeString(player->getDetails()->motto);
        response.writeString("");
        response.writeBool(false);
        response.writeInt(0); // Respect
        response.writeInt(3); // Daily Respect Points
        response.writeInt(3); // Daily Pet Respect Points
        response.writeBool(true);
        response.writeString("1448526834");
        response.writeBool(true);
        response.writeBool(false);
        return response;
    }

    const int getHeader() const {
        return Outgoing::UserObjectMessageComposer;
    }

private:
    Player *player;

};
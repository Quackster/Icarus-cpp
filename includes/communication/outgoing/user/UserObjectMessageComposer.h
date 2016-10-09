#pragma once
#include <string>

#include "game/player/Player.h"
#include "communication/outgoing/MessageComposer.h"

class UserObjectMessageComposer : public MessageComposer {

public:
    UserObjectMessageComposer(Player *player) : player(player) { }

    Response compose() {
        Response response = this->createResponse();
        response.writeInt(player->getDetails()->getId());
        response.writeString(player->getDetails()->getUsername());
        response.writeString(player->getDetails()->getFigure());
        response.writeString("M");
        response.writeString(player->getDetails()->getMotto());
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

    int getHeader() {
        return Outgoing::UserObjectMessageComposer;
    }

private:
    Player *player;

};
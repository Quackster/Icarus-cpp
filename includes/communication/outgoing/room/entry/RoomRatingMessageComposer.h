#pragma once

#include "game/room/Room.h"
#include "game/player/Player.h"

#include "communication/outgoing/MessageComposer.h"

class RoomRatingMessageComposer : public MessageComposer {

public:
    RoomRatingMessageComposer(int score)
        : score(score) { }

    Response compose() {
        Response response = this->createResponse();
        response.writeInt(this->score);
        response.writeBool(false);
        return response;
    }

    int getHeader() {
        return Outgoing::RoomRatingMessageComposer;
    }

private:
    int score;
};
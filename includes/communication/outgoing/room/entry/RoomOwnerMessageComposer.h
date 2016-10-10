#pragma once

#include "game/room/Room.h"
#include "game/player/Player.h"

#include "communication/outgoing/MessageComposer.h"

class RoomOwnerMessageComposer : public MessageComposer {

public:
    RoomOwnerMessageComposer() { }

    Response compose() {
        Response response = this->createResponse();
        return response;
    }

    int getHeader() {
        return Outgoing::HasOwnerRightsMessageComposer;
    }

};
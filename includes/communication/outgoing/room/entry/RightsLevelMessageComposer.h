#pragma once

#include "game/room/Room.h"
#include "game/player/Player.h"

#include "communication/outgoing/MessageComposer.h"

class RoomDataMessageComposer : public MessageComposer {

public:
    RoomDataMessageComposer(int rights_level) : rights_level(rights_level) { }

    Response compose() {
        Response response = this->createResponse();
        response.writeInt(rights_level);
        return response;
    }

    int getHeader() {
        return Outgoing::RightsLevelMessageComposer;
    }

private:
    int rights_level;

};
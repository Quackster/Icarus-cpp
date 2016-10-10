#pragma once

#include "game/room/Room.h"
#include "game/player/Player.h"

#include "communication/outgoing/MessageComposer.h"

class PrepareRoomMessageComposer : public MessageComposer {

public:
    PrepareRoomMessageComposer(int room_id) : 
        room_id(room_id) { }

    Response compose() {
        Response response = this->createResponse();
        response.writeInt(this->room_id);
        return response;
    }

    int getHeader() {
        return Outgoing::RoomUpdateMessageComposer;
    }

private:
    int room_id;
};
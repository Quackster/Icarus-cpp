#pragma once

#include "game/room/Room.h"
#include "game/player/Player.h"

#include "communication/outgoing/MessageComposer.h"

class RoomModelMessageComposer : public MessageComposer {

public:
    RoomModelMessageComposer(std::string model_name, int room_id) 
        : model_name(model_name), room_id(room_id) { }

    Response compose() {
        Response response = this->createResponse();
        response.writeString(this->model_name);
        response.writeInt(this->room_id);
        return response;
    }

    int getHeader() {
        return Outgoing::InitialRoomInfoMessageComposer;
    }

private:
    std::string model_name;
    int room_id
};
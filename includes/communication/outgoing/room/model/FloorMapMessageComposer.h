#pragma once

#include "boot/Icarus.h"
#include "game/room/model/RoomModel.h"

#include "game/room/Room.h"
#include "game/player/Player.h"

#include "communication/outgoing/MessageComposer.h"

class FloorMapMessageComposer : public MessageComposer {

public:
    FloorMapMessageComposer(Room *room) : room(room) { }

    Response compose() {

        RoomModel *model = room->getData()->getModel();

        Response response = this->createResponse();
        response.writeBool(true);
        response.writeInt(room->getData()->getWallHeight());
        response.writeString(model->getFloorMap());

        std::cout << model->getFloorMap() << std::endl;

        return response;
    }

    int getHeader() {
        return Outgoing::FloorMapMessageComposer;
    }

private:
    Room *room;

};
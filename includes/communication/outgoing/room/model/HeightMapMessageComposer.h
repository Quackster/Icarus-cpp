#pragma once

#include "boot/Icarus.h"
#include "game/room/model/RoomModel.h"

#include "game/room/Room.h"
#include "game/player/Player.h"

#include "communication/outgoing/MessageComposer.h"

class HeightMapMessageComposer : public MessageComposer {

public:
    HeightMapMessageComposer(Room *room) : room(room) { }

    Response compose() {

        RoomModel *model = room->getData()->getModel();

        if (model == nullptr) {
        }

        Response response = this->createResponse();
        response.writeInt(model->getMapSizeX());
        response.writeInt(model->getMapSizeX() * model->getMapSizeY());

        for (int y = 0; y < model->getMapSizeY(); y++) {
            for (int x = 0; x < model->getMapSizeX(); x++) {
            }
        }

        return response;
    }

    int getHeader() {
        return Outgoing::HeightMapMessageComposer;
    }

private:
    Room *room;

};
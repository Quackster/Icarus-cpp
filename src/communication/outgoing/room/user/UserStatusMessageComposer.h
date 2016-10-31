/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <map>

#include "game/entities/Entity.h"
#include "communication/outgoing/MessageComposer.h"

class UserStatusMessageComposer : public MessageComposer {

public:
    UserStatusMessageComposer(Entity *entity) {
        this->entities = { entity };
    }

    UserStatusMessageComposer(std::map<int, Entity*> entities) {
        for (auto kvp : entities) {
            this->entities.push_back(kvp.second);
        }
    }

    UserStatusMessageComposer(std::vector<Entity*> entities) :
        entities(entities) {  }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->entities.size());

        for (auto entity : entities) {

            RoomUser *room_user = entity->getRoomUser();

            response.writeInt(room_user->getVirtualId());
            response.writeInt(room_user->getX());
            response.writeInt(room_user->getY());
            response.writeString(std::to_string(room_user->getHeight()));
            response.writeInt(room_user->getHeadRotation());
            response.writeInt(room_user->getRotation());

            if (room_user->isWalking()) {
                if (!room_user->getNext().isEmpty()) {

                    Position next = room_user->getNext();
                    int height = room_user->getRoom()->getModel()->getSquareHeight()[next.getX() * room_user->getRoom()->getModel()->getMapSizeY() + next.getY()];

                    room_user->setX(next.getX());
                    room_user->setY(next.getY());
                    room_user->setHeight(height);
                }
                else {
                    room_user->setStatus("mv", "");
                    room_user->setWalking(false);
                    room_user->stopWalking();
                }
            }

            std::string status = "/";

            for (auto kvp : room_user->getStatuses()) {
                status += kvp.first + " " + kvp.second + "/";
            }

            response.writeString(status + "/");

            if (room_user->getNeedsUpdate()) {
                room_user->setNeedsUpdate(false);
            }
        }

        return response;
    }

    const int getHeader() const {
        return Outgoing::UserStatusMessageComposer;
    }

private:
    std::vector<Entity*> entities;
};
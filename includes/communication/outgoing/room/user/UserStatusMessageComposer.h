/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "game/entities/Entity.h"
#include "communication/outgoing/MessageComposer.h"

class UserStatusMessageComposer : public MessageComposer {

public:
    UserStatusMessageComposer(Entity *entity) {
        this->entities = { entity };
    }

    UserStatusMessageComposer(std::vector<Entity*> entities) :
        entities(entities) {  }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->entities.size());

        for (auto entity : entities) {
            response.writeInt(entity->getRoomUser()->getVirtualId());
            response.writeInt(entity->getRoomUser()->getX());
            response.writeInt(entity->getRoomUser()->getY());
            response.writeString(std::to_string(entity->getRoomUser()->getHeight()));
            response.writeInt(entity->getRoomUser()->getHeadRotation());
            response.writeInt(entity->getRoomUser()->getRotation());

            std::string status = "/";

            for (auto kvp : entity->getRoomUser()->getStatuses()) {
                status += kvp.first + " " + kvp.second + "/";
            }

            response.writeString(status + "/");

            std::cout << " User status: " << status << std::endl;
        }

        return response;
    }

    const int getHeader() const {
        return Outgoing::UserStatusMessageComposer;
    }

private:
    std::vector<Entity*> entities;
};
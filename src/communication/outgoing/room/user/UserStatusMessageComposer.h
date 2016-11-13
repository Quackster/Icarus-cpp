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
            room_user->awake();

            response.writeInt(room_user->virtual_id);
            response.writeInt(room_user->position.x);
            response.writeInt(room_user->position.y);
            response.writeString(std::to_string(room_user->height));
            response.writeInt(room_user->head_rotation);
            response.writeInt(room_user->rotation);

            room_user->walk();

            std::string status = "/";

            for (auto kvp : room_user->getStatuses()) {
                status += kvp.first + " " + kvp.second + "/";
            }

            response.writeString(status + "/");

            if (room_user->needs_update) {
                room_user->needs_update = false;
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
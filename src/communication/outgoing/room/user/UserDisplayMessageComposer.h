/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <string>
#include <map>

#include "game/entities/Entity.h"
#include "communication/outgoing/MessageComposer.h"

class UserDisplayMessageComposer : public MessageComposer {

public:
    UserDisplayMessageComposer(Entity *entity) {
        this->entities = { entity };
    }

    UserDisplayMessageComposer(std::map<int, Entity*> entities) {
        for (auto kvp : entities) {
            this->entities.push_back(kvp.second);
        }
    }

    UserDisplayMessageComposer(std::vector<Entity*> entities) :
        entities(entities) {  }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->entities.size());

        for (auto entity : entities) {
            response.writeInt(entity->getDetails()->id);
            response.writeString(entity->getDetails()->username);
            response.writeString(entity->getDetails()->motto);
            response.writeString(entity->getDetails()->figure);
            response.writeInt(entity->getRoomUser()->virtual_id);
            response.writeInt(entity->getRoomUser()->position.x);
            response.writeInt(entity->getRoomUser()->position.y);
            response.writeString(std::to_string(entity->getRoomUser()->height));
            response.writeInt(0);

            if (entity->getEntityType() == PLAYER) {
                response.writeInt(1);
            }

            if (entity->getEntityType() == BOT) {
                response.writeInt(4);
            }

            response.writeString("m");

            if (entity->getEntityType() == PLAYER) {
                response.writeInt(-1);
                response.writeInt(-1);
                response.writeInt(0);
                response.writeInt(1337);
                response.writeBool(false);
            }

            if (entity->getEntityType() == BOT) {

                response.writeInt(1);
                response.writeString("Alex");

                response.writeInt(5);
                response.writeShort(1);
                response.writeShort(2);
                response.writeShort(3);
                response.writeShort(4);
                response.writeShort(5);
            }
        }

        return response;
    }

    const int getHeader() const {
        return Outgoing::UserDisplayMessageComposer;
    }

private:
    std::vector<Entity*> entities;
};
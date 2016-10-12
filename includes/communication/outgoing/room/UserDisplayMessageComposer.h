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

#include "game/entities/Entity.h"
#include "communication/outgoing/MessageComposer.h"

class UserDisplayMessageComposer : public MessageComposer {

public:
    UserDisplayMessageComposer(Entity *entity) { 
        this->entities = { entity };
    }

    UserDisplayMessageComposer(std::vector<Entity*> entities) :
        entities(entities) {  }

    Response compose() {
        Response response = this->createResponse();
        response.writeInt(this->entities.size());

        for (auto entity : entities) {
            response.writeInt(entity->getDetails()->getId());
            response.writeString(entity->getDetails()->getUsername());
            response.writeString(entity->getDetails()->getMotto());
            response.writeString(entity->getDetails()->getFigure());
            response.writeInt(entity->getRoomUser()->getVirtualId());
            response.writeInt(entity->getRoomUser()->getX());
            response.writeInt(entity->getRoomUser()->getY());
            response.writeString(std::to_string(entity->getRoomUser()->getHeight()));
            response.writeInt(0);
            response.writeInt(1);
            response.writeString("m");
            response.writeInt(-1);
            response.writeInt(-1);
            response.writeInt(0);
            response.writeInt(1337);
            response.writeBool(false);
        }

        return response;
    }

    int getHeader() {
        return Outgoing::UserDisplayMessageComposer;
    }

private:
    std::vector<Entity*> entities;
};
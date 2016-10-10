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

    Response compose() {
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
        }

        return response;
    }

    int getHeader() {
        return Outgoing::UserStatusMessageComposer;
    }

private:
    std::vector<Entity*> entities;
};
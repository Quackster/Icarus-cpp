/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include <thread>
#include <chrono>
#include <sstream>

#include "boot/Icarus.h"

#include "communication/outgoing/room/user/UserStatusMessageComposer.h"

#include "game/room/model/Rotation.h"
#include "game/room/tasks/RoomRunnable.h"

/*
    Constructor for room runnable
*/
RoomRunnable::RoomRunnable(Room *room) : 
    room(room) { }

/*
Tick handler for room runnable

@return none
*/
void RoomRunnable::run() {

    if (this->room == nullptr ||
        this->room->isDisposed() ||
        this->room->getEntities().size() == 0) {
        this->room->setRunnable(nullptr);
        return;
    }

    std::vector<Entity*> update_entities;

    RoomModel *room_model = this->room->getModel();

    mtx.lock(); // Lock entities thread

    std::map<int, Entity*> entities = this->room->getEntities();

    for (int i = 0; i < entities.size(); i++) {

        Entity *entity = entities[i];

        if (entity != nullptr) {
            if (entity->getRoomUser() != nullptr) {

                this->processEntity(entity);

                RoomUser *room_user = entity->getRoomUser();

                if (room_user->getNeedsUpdate()) {
                    update_entities.push_back(entity);
                }
            }
        }
    }

    mtx.unlock(); // Unlock entities thread

    this->room->send(UserStatusMessageComposer(update_entities));

    if (room->getPlayers().size() > 0 && this->room->getRunnable() != nullptr) {
        Icarus::getGame()->getGameScheduler()->schedule(this->room->getRunnable());
    }
    else {
        this->room->setRunnable(nullptr);
    }
}

void RoomRunnable::processEntity(Entity *entity) {

    RoomUser *room_user = entity->getRoomUser();

    if (Icarus::getUnixTimestamp() > room_user->getSignTime()) {
        if (room_user->containsStatus("sign")) {
            room_user->setStatus("sign", "");
            room_user->setNeedsUpdate(true);
        }
    }

    if (room_user->isWalking()) {
        if (room_user->getPath().size() > 0) {

            Position next = room_user->getPath().front();

            room_user->getPath().pop_front();

            room_user->setStatus("lay", "");
            room_user->setStatus("sit", "");

            int rotation = Rotation::getRotation(room_user->getPosition().getX(), room_user->getPosition().getY(), next.getX(), next.getY());
            int height = this->room->getModel()->getSquareHeight(next.getX(), next.getY());

            room_user->setRotation(rotation, true, false);

            std::stringstream ss;
            ss << next.getX();
            ss << ",";
            ss << next.getY();
            ss << ",";
            ss << height;

            room_user->setStatus("mv", ss.str());
            room_user->setNext(next);  
            room_user->setNeedsUpdate(true);
        }
        else {
            room_user->setNext(Position());
            room_user->setNeedsUpdate(true);
        }

    }
}
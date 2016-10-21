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

#include "game/room/model/Rotation.h"
#include "game/room/tasks/RoomRunnable.h"

/*
    Constructor for room runnable
*/
RoomRunnable::RoomRunnable(Room *room) : room(room) { }

/*
Tick handler for room runnable

@return none
*/
void RoomRunnable::run() {

    if (this->room->isDisposed() || this->room->getData() == nullptr || this->room->getEntities() == nullptr) {
        this->room->setRunnable(nullptr);
        return;
    }

    RoomModel *room_model = this->room->getModel();

    for (auto kvp: *this->room->getEntities()) {

        Entity *entity = kvp.second;
        RoomUser *room_user = entity->getRoomUser();

        if (room_user->isWalking()) {

            if (room_user->getPath().size() > 0) {

                Position next = room_user->getPath().front();
                room_user->getPath().pop_front();

                room_user->setStatus("lay", "");
                room_user->setStatus("sit", "");

                int rotation = Rotation::getRotation(room_user->getPosition().getX(), room_user->getPosition().getY(), next.getX(), next.getY());
                int height = room_model->getSquareHeight()[next.getX() * room_model->getMapSizeY() + next.getY()];

                room_user->setRotation(rotation, true, false);

                std::stringstream ss;
                ss << next.getX();
                ss << ",";
                ss << next.getY();
                ss << ",";
                ss << height;

                room_user->setStatus("mv", ss.str());
                room_user->updateStatus();
                room_user->setX(next.getX());
                room_user->setY(next.getY());
                room_user->setHeight(height);
            }
            else {
                room_user->setStatus("mv", "");
                room_user->setWalking(false);
                room_user->updateStatus();
            }

        }
    }

    if (room->getPlayers().size() > 0 && this->room->getRunnable() != nullptr) {
        Icarus::getGame()->getGameScheduler()->schedule(/*std::make_shared<RoomRunnable>(this->room)*/this->room->getRunnable());
    }
}
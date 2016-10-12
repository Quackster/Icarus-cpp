/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "boot/Icarus.h"
#include "game/room/tasks/RoomRunnable.h"
#include "communication/outgoing/room/UserStatusMessageComposer.h"

/*
    Constructor for room runnable
*/
RoomRunnable::RoomRunnable(Room *room) : room(room) { }

/*
    Tick handler for room runnable

    @return none
*/
void RoomRunnable::run() {

    if (room->isDisposed()) {
        return;
    }

    std::vector<Entity*> entities_update;

    for (Entity *entity : *this->room->getEntities()) {

        RoomUser *room_user = entity->getRoomUser();

        if (room_user->getPosition().sameAs(room_user->getGoal())) {
            room_user->stopWalking(false);
        }

        if (room_user->isWalking()) {

            if (room_user->getPath().size() > 0) {

                Position next = room_user->getPath().front();
                room_user->getPath().pop_front(); // remove front



                if (room_user->getStatuses().count("mv") > 0) {
                    room_user->getStatuses().erase("mv"); // remove status
                }

                if (room_user->getStatuses().count("sit") > 0) {
                    room_user->getStatuses().erase("sit"); // remove status
                }

                if (room_user->getStatuses().count("lay") > 0) {
                    room_user->getStatuses().erase("lay"); // remove status
                }

                std::string status = std::to_string(next.getX()) = " ," + std::to_string(next.getY()) = " ,0";
                room_user->getStatuses().insert(std::make_pair("mv", status));


                           /* # Update collision map
                            if not self.room.data.allow_walkthrough:
                self.room.room_mapping.update_map(room_user.position.x, room_user.position.y, False)
                    self.room.room_mapping.update_map(next.x, next.y, True)*/
                room_user->setX(next.getX());
                room_user->setY(next.getY());

                    //room_user.position.z = height               
                
                //printf("virtual id: %i\n", room_user->getStatuses().size());


            }
            else {
                room_user->stopWalking(true);
            }

        }
        else if (room_user->getNeedsUpdate()) {
            room_user->stopWalking(false);
            entities_update.push_back(entity);
        }
    }

    if (entities_update.size() > 0) {
        this->room->send(UserStatusMessageComposer(entities_update));
    }

    this->room->scheduleRunnable(); // reschedule again!!
}
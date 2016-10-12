/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "communication/incoming/MessageEvent.h"
#include "game/pathfinder/Pathfinder.h"

class WalkMessageEvent : public MessageEvent {

public:
    WalkMessageEvent() { }

    void handle(Player *player, Request &request) {

        int goal_x = request.readInt();
        int goal_y = request.readInt();

        Room *room = player->getRoomUser()->getRoom();

        RoomUser *room_user = player->getRoomUser();
        room_user->setGoalX(goal_x);
        room_user->setGoalY(goal_y);
        room_user->setPath(Pathfinder::makePath(room_user->getPosition(), room_user->getGoal(), room));
        room_user->setWalking(true);

        printf(" size %i\n", room_user->getPath().size());
    }
};
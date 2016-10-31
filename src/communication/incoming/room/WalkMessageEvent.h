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

        Room *room = player->getRoomUser()->getRoom();

        if (room == nullptr) {
            return;
        }

        int goal_x = request.readInt();
        int goal_y = request.readInt();


        RoomUser *room_user = player->getRoomUser();

        room_user->setGoalX(goal_x);
        room_user->setGoalY(goal_y);

        Position goal = room_user->getGoal();
        Position current = room_user->getPosition();

        int map_size_x = room->getModel()->getMapSizeX();
        int map_size_y = room->getModel()->getMapSizeY();

        if (goal.getX() >= map_size_x || goal.getY() >= map_size_y) {
            return;
        }

        if (goal.getX() == current.getX() && goal.getY() == current.getY()) {
            return;
        }

        if (!Pathfinder::isValidStep(room, current, goal, false)) {
            return;
        }

        auto path = Pathfinder::makePath(room_user->getPosition(), room_user->getGoal(), room);

        if (path.size() == 0) {
            return; // TODO: Call pathfinder to retry again.
        }

        room_user->setPath(path);
        room_user->setWalking(true);
    }
};
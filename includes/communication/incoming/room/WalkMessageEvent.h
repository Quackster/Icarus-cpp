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

        std::vector<Position> paths = Pathfinder::makePath(room_user->getPosition(), room_user->getGoal(), room);
    }
};
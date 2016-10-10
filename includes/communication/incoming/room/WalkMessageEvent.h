#pragma once
#include "communication/incoming/MessageEvent.h"
#include "game/pathfinder/Pathfinder.h"

class WalkMessageEvent : public MessageEvent {

public:
    WalkMessageEvent() { }

    void handle(Player *player, Request &request) {

        int goal_x = request.readInt();
        int goal_y = request.readInt();

        Position current = Position(player->getRoomUser()->getX(), player->getRoomUser()->getY());
        Position goal = Position(goal_x, goal_y);
        Room *room = player->getRoomUser()->getRoom();

        std::vector<Position> paths = Pathfinder::makePath(current, goal, room);

        for (auto path : paths) {
            std::cout << path.toString() << std::endl;
        }
    }
};
#pragma once
#include <thread>
#include <chrono>

#include "communication/outgoing/room/UserStatusMessageComposer.h"
#include "communication/incoming/MessageEvent.h"
#include "game/pathfinder/Pathfinder.h"

class WalkMessageEvent : public MessageEvent {

public:
    WalkMessageEvent() { }

    void handle(Player *player, Request &request) {

        int goal_x = request.readInt();
        int goal_y = request.readInt();

        printf(" walk req: %i, %i\n", goal_x, goal_y);

        Room *room = player->getRoomUser()->getRoom();

        RoomUser *room_user = player->getRoomUser();
        RoomModel *room_model = room->getData()->getModel();

        Position current = Position(room_user->getX(), room_user->getY());
        Position goal = Position(goal_x, goal_y);

};

/* points.push_back(Position(0, -1));
        points.push_back(Position(0, 1));
        points.push_back(Position(1, 0));
        points.push_back(Position(-1, 0));
        points.push_back(Position(1, -1));
        points.push_back(Position(-1, 1));
        points.push_back(Position(1, 1));
        points.push_back(Position(-1, -1));*/
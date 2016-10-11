#pragma once
#include <queue>

#include "game/pathfinder/Position.h"
#include "game/room/RoomUser.h"

class RoomUser;
class Pathfinder
{
public:
    Pathfinder();
    Pathfinder(RoomUser *room_user);
    ~Pathfinder();

    void moveTo(Position position);
    Position getNextStep();
    std::queue<Position*> findPath();

    Position getTarget() { return target; }
    void setTarget(Position target) { this->target = target; }
    bool isCompleted() { return path.size() == 0; }
    void clear() {

        std::queue<Position*> paths;
        std::swap(this->path, paths);

    }
    std::queue<Position*> getPath() { return path;  }

private:
    RoomUser *room_user;
    Position target;
    std::queue<Position*> path;
};


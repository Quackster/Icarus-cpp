#pragma once
#include "game/room/Room.h"
#include "game/pathfinder/Position.h"
#include "game/pathfinder/Position.h"

class PathfinderNode
{

public:
    PathfinderNode();
    PathfinderNode(Position position);
    ~PathfinderNode();

    PathfinderNode *getNextNode() { return node; }
    bool getInOpen() { return in_open; }
    bool getInClose() { return in_close; }
    Position getPosition() { return position; }
    int getCost() { return cost;  }

    void setNextNode(PathfinderNode *node) { this->node = node; }
    void setInOpen(bool in_open) { this->in_open = in_open; }
    void setInClose(bool in_close) { this->in_close = in_close; }
    void setPosition(Position position) { this->position = position; }
    void setCost(int cost) { this->cost = cost; }

private:
    PathfinderNode *node;
    bool in_open;
    bool in_close;
    Position position;
    int cost;
};


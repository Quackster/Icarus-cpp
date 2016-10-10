#include "stdafx.h"
#include "game/pathfinder/PathfinderNode.h"


PathfinderNode::PathfinderNode() : position(Position(0, 0)) {

    
}

PathfinderNode::PathfinderNode(Position position) :
    node(nullptr), in_open(in_open), in_close(in_close), position(position), cost(/*99999999*/0) { }


PathfinderNode::~PathfinderNode()
{
}

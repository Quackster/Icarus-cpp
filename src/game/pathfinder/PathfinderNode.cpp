#include "stdafx.h"
#include "game/pathfinder/PathfinderNode.h"


PathfinderNode::PathfinderNode() :
    position(Position(0, 0)), node(nullptr), in_open(false), in_close(false), cost(99999999)
{

    
}

PathfinderNode::PathfinderNode(Position position) :
    node(nullptr), in_open(false), in_close(false), position(position), cost(99999999) { }


PathfinderNode::~PathfinderNode()
{
}

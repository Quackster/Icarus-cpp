/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
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

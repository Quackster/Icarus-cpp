#include "stdafx.h"
#include "game/pathfinder/Position.h"

Position::Position() :
    x(-999), y(-999) {
}


Position::Position(int x, int y) :
    x(x), y(y) {
}

Position::~Position()
{
}

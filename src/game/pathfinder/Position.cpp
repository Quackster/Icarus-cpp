/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"
#include "game/pathfinder/Position.h"

Position::Position() :
    x(-999), y(-999) { }

Position::Position(int x, int y) :
    x(x), y(y) { }


Position::~Position()
{
}

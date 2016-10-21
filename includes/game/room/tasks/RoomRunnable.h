/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "thread/Runnable.h"
#include "game/room/Room.h"

class RoomRunnable : public Runnable {

public:
    RoomRunnable(Room *room);
    void run();
    void processEntity(Entity *entity);
    Room *room;
    bool cancelled = true;

};
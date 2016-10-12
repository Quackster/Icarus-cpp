/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "boot/Icarus.h"
#include "game/room/tasks/RoomRunnable.h"

/*
    Constructor for room runnable
*/
RoomRunnable::RoomRunnable(Room *room) : room(room) { }

/*
    Tick handler for room runnable

    @return none
*/
void RoomRunnable::run() {

    if (room->isDisposed()) {
        return;
    }



    this->room->scheduleRunnable(); // reschedule again!!
}
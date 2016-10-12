#pragma once
#include "thread/Runnable.h"
#include "game/room/Room.h"

class RoomRunnable : public Runnable {

public:
    RoomRunnable(Room *room);
    void run();
    Room *room;
};
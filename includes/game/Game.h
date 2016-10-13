/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "game/navigator/NavigatorManager.h"
#include "game/room/RoomManager.h"
#include "thread/ExecutorService.h"

class Game
{
public:
    Game();
    ~Game();

    NavigatorManager *getNavigatorManager() { return navigator_manager; }
    ExecutorService *getGameScheduler() { return executor_service; }
    RoomManager *getRoomManager() { return room_manager; }

private:
    NavigatorManager *navigator_manager;
    ExecutorService *executor_service;
    RoomManager *room_manager;
};




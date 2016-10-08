#pragma once
#include "game/navigator/NavigatorManager.h"
#include "thread/ExecutorService.h"

class Game
{
public:
    Game();
    ~Game();

    NavigatorManager *getNavigatorManager() { return navigator_manager; }
    ExecutorService *getGameScheduler() { return executor_service; }

private:
    NavigatorManager *navigator_manager;
    ExecutorService *executor_service;
};




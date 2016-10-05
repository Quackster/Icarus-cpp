#include "stdafx.h"
#include "game/Game.h"

Game::Game() {
    this->navigatorManager = new NavigatorManager();
    this->executorService = ExecutorService::createSchedulerService(configuration->getInt("room.thread.pool.size"));
}


Game::~Game() {
    delete this->navigatorManager;
}

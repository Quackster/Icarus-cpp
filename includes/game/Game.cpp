#include "stdafx.h"
#include "game/Game.h"

Game::Game() {
    this->navigatorManager = new NavigatorManager();
    this->executorService = ExecutorService::createSchedulerService(4);
}


Game::~Game() {
    delete this->navigatorManager;
}

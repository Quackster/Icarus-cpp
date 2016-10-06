#include "stdafx.h"

#include "boot/Icarus.h"
#include "game/Game.h"

Game::Game() {
    this->navigatorManager = new NavigatorManager();
    this->executorService = ExecutorService::createSchedulerService(Icarus::getConfiguration()->getInt("room.thread.pool.size"), std::chrono::milliseconds(500));
}


Game::~Game() {
    delete this->navigatorManager;
}

#include "stdafx.h"

#include "boot/Icarus.h"
#include "game/Game.h"

Game::Game() {
    this->navigator_manager = new NavigatorManager();
    this->executor_service = ExecutorService::createSchedulerService(Icarus::getConfiguration()->getInt("room.thread.pool.size"), std::chrono::milliseconds(500));
}


Game::~Game() {
    delete this->navigator_manager;
}

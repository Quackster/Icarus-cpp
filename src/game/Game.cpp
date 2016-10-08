#include "stdafx.h"

#include "boot/Icarus.h"
#include "game/Game.h"

Game::Game() : 
    navigator_manager(new NavigatorManager()), 
    executor_service(ExecutorService::createSchedulerService(Icarus::getConfiguration()->getInt("thread.pool.size"), std::chrono::milliseconds(500))) {
}


Game::~Game() {
    delete this->navigator_manager;
}

#include "stdafx.h"

#include "boot/Icarus.h"
#include "game/Game.h"

Game::Game() :
    navigator_manager(new NavigatorManager()),
    room_manager(new RoomManager()),
    executor_service(ExecutorService::createSchedulerService(Icarus::getConfiguration()->getInt("thread.pool.size"), std::chrono::milliseconds(500))) {
}


Game::~Game() {

    // Stop executor service
    this->executor_service->stop();

    // Delete pointers
    delete this->navigator_manager;
    delete this->room_manager;
    delete this->executor_service;
}

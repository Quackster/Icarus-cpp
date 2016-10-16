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
#include "game/Game.h"

#include "dao/RoomDao.h"

Game::Game() :
    navigator_manager(new NavigatorManager()),
    room_manager(new RoomManager()),
    executor_service(ExecutorService::createSchedulerService(Icarus::getConfiguration()->getInt("thread.pool.size"), std::chrono::milliseconds(500))) {
}

/*
    Function that loads data after everything else needed to be loaded first

    @return none
*/
void Game::createGame() {
    RoomDao::addPublicRooms();
}

Game::~Game() {

    // Stop executor service
    this->executor_service->stop();

    // Delete pointers
    delete this->navigator_manager;
    delete this->room_manager;
    delete this->executor_service;
}

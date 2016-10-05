#include "stdafx.h"
#include "game/Game.h"

Game::Game() {
    this->navigatorManager = new NavigatorManager();
}


Game::~Game() {
    delete this->navigatorManager;
}

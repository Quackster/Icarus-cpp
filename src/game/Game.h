#pragma once
#include "game/navigator/NavigatorManager.h"

class Game
{
public:
    Game();
    ~Game();

    NavigatorManager *getNavigatorManager() { return navigatorManager; }

private:
    NavigatorManager *navigatorManager;
};


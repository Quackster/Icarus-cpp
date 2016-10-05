#pragma once
#include <vector>

#include "game/navigator/NavigatorTab.h"

class NavigatorManager
{
public:
    NavigatorManager();
    ~NavigatorManager();

private:
    vector<NavigatorTab*> *tabs;
};


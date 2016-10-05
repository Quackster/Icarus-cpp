#pragma once
#include <vector>

#include "game/navigator/NavigatorTab.h"
#include "game/navigator/NavigatorCategory.h"

class NavigatorManager
{
public:
    NavigatorManager();
    ~NavigatorManager();

    vector<NavigatorTab*> *getTabs() { return tabs; }
    vector<NavigatorCategory*> *getCategories() { return categories; }
    

private:
    vector<NavigatorTab*> *tabs;
    vector<NavigatorCategory*> *categories;
};


#pragma once
#include <vector>

#include "game/navigator/NavigatorTab.h"
#include "game/navigator/NavigatorCategory.h"

class NavigatorManager
{
public:
    NavigatorManager();
    ~NavigatorManager();

    NavigatorTab *getTab(std::string tab_name);
    std::vector<NavigatorTab*> getParentTabs();
    std::vector<NavigatorTab*> *getTabs() { return tabs; }
    std::vector<NavigatorCategory*> *getCategories() { return categories; }
    

private:
    std::vector<NavigatorTab*> *tabs;
    std::vector<NavigatorCategory*> *categories;
};


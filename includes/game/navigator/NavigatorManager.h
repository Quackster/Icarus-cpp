#pragma once
#include <vector>
#include <map>

#include "game/navigator/NavigatorTab.h"
#include "game/navigator/NavigatorCategory.h"

#include "game/room/populators/RoomPopulator.h"

class NavigatorManager
{
public:
    NavigatorManager();
    ~NavigatorManager();

    NavigatorTab *getTab(std::string tab_name);
    std::vector<NavigatorTab*> getParentTabs();
    std::vector<NavigatorTab*> *getTabs() { return tabs; }
    std::vector<NavigatorCategory*> *getCategories() { return categories; }
    RoomPopulator *getPopulator(std::string name);
    

private:
    std::vector<NavigatorTab*> *tabs;
    std::vector<NavigatorCategory*> *categories;
    std::map<std::string, RoomPopulator*> *room_populators;
};


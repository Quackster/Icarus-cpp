#include "stdafx.h"

#include "boot/Icarus.h"
#include "game/navigator/NavigatorTab.h"

/*
    Constructor for Navigator tab
*/
NavigatorTab::NavigatorTab(int id, int childId, std::string tabName, std::string title, char buttonType, bool closed, bool thumbnail) :
    id(id), childId(childId), tabName(tabName), title(title), buttonType(buttonType), closed(closed), thumbnail(thumbnail)
{
}

/*
    Get all child tabs under this tab

    @return list of child tabs
*/
std::vector<NavigatorTab*> NavigatorTab::getChildTabs() {

    std::vector<NavigatorTab*> tabs = std::vector<NavigatorTab*>();

    for (auto tab : *Icarus::getGame()->getNavigatorManager()->getTabs()) {
        if (tab->getChildId() == this->id) {
            tabs.push_back(tab);
        }
    }

    return tabs;
}


/*
    Deconstructor for navigator tab
*/
NavigatorTab::~NavigatorTab()
{
}

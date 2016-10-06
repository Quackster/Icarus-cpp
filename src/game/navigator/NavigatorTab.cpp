#include "stdafx.h"

#include "boot\Icarus.h"
#include "game/navigator/NavigatorTab.h"

/*
    Constructor for Navigator tab
*/
NavigatorTab::NavigatorTab(int id, int child_id, string tabName, string title, char button_type, bool closed, bool thumbnail) :
    id(id), childId(child_id), tabName(tabName), title(title), buttonType(button_type), closed(closed), thumbnail(thumbnail)
{
}

/*
    Get all child tabs under this tab

    @return list of child tabs
*/
vector<NavigatorTab*> NavigatorTab::getChildTabs() {

    vector<NavigatorTab*> tabs = vector<NavigatorTab*>();

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

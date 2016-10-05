#include "stdafx.h"

#include "boot\Icarus.h"
#include "game/navigator/NavigatorTab.h"

/*
    Constructor for Navigator tab
*/
NavigatorTab::NavigatorTab(int id, int child_id, string tab_name, string title, char button_type, bool closed, bool thumbnail) :
    id(id), child_id(child_id), tab_name(tab_name), title(title), button_type(button_type), closed(closed), thumbnail(thumbnail)
{
}

/*
    Get all child tabs under this tab

    @return list of child tabs
*/
vector<NavigatorTab*> NavigatorTab::getChildTabs() {

    vector<NavigatorTab*> tabs = vector<NavigatorTab*>();

    for (auto tab : *Icarus::getGame()->getNavigatorManager()->getTabs()) {
        if (tab->getChildId() == this->child_id) {
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

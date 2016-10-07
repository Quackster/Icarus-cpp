#include "stdafx.h"
#include "dao/NavigatorDao.h"
#include "game/navigator/NavigatorManager.h"

/*
Constructor for Navigator Manager

Initialises the list for storing navigator tabs
*/
NavigatorManager::NavigatorManager() {
    this->tabs = NavigatorDao::getTabsByChildId(-1);
    this->categories = NavigatorDao::getCategories();
}

/*
    Gets tab by name

    @param tab name
    @return tab ptr
*/
NavigatorTab* NavigatorManager::getTab(std::string tabName) {

    for (auto tab : *this->tabs) {
        if (tab->getTabName() == tabName) {
            return tab;
        }
    }

    return nullptr;
}

/*
    Returns all parent tabs, (those who have -1 as child id
    @return vector list of parent tabs
*/
std::vector<NavigatorTab*> NavigatorManager::getParentTabs() {

    std::vector<NavigatorTab*> tabs = std::vector<NavigatorTab*>();

    for (auto tab : *this->tabs) {
        if (tab->getChildId() == -1) {
            tabs.push_back(tab);
        }
    }

    return tabs;
}

/*
Deconstructor for Navigator Manager

Deletes all pointer variables
*/
NavigatorManager::~NavigatorManager() {

    for (auto tab : *this->tabs) {
        delete tab; // Delete tab pointer
    }

    for (auto category : *this->categories) {
        delete category; // Delete categories pointer
    }

    // Empty out nullptr values
    this->categories->clear();
    this->tabs->clear();

    // Delete lists
    delete categories;
    delete tabs;
}

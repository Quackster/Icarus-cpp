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
Deconstructor for Navigator Manager

Deletes all pointer variables
*/
NavigatorManager::~NavigatorManager() {

    for (auto tab : *this->tabs) {
        delete tab; // Delete tab pointer
    }

    for (auto tab : *this->categories) {
        delete tab; // Delete categories pointer
    }

    // Empty out nullptr values
    this->categories->clear();
    this->tabs->clear();

    // Delete lists
    delete categories;
    delete tabs;
}

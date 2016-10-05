#include "stdafx.h"
#include "game/navigator/NavigatorManager.h"

/*
Constructor for Navigator Manager

Initialises the list for storing navigator tabs
*/
NavigatorManager::NavigatorManager() {
    this->tabs = new vector<NavigatorTab*>();
}

/*
Deconstructor for Navigator Manager

Deletes all pointer variables
*/
NavigatorManager::~NavigatorManager() {

    for (auto tab : *this->tabs) {
        delete tab; // Delete tab pointer
    }

    // Empty out nullptr values
    this->tabs->clear();

    // Delete tab list
    delete tabs;
}


/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <stdafx.h>

#include "InteractorManager.h"

#include "interactors/DefaultInteractor.h"
#include "interactors/GateInteractor.h"

/*
    Constructor for Interactor Manager

    Initialises the list for storing item interaction types
*/
InteractorManager::InteractorManager() {
    this->interactors["default"] = new DefaultInteractor();
    this->interactors["gate"] = new GateInteractor();
}

/*
    Gets the interactor for a interaction type, will return nullptr if nothing was supplied

    @return base interactor
*/
BaseInteractor *InteractorManager::getInteractor(std::string interaction_type) {

    if (this->interactors.count(interaction_type) > 0) {
        return this->interactors.find(interaction_type)->second;
    }

    return nullptr;
}

/*
    Deconstructor for Interactor Manager

    Deletes list for storing item interaction types
*/
InteractorManager::~InteractorManager() {

}

/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/

#include "stdafx.h"

#include "dao/ItemDao.h"

#include "Item.h"
#include "definitions/ItemDefinition.h"

#include "ItemManager.h"

/*
    Constructor for Furniture
*/
ItemManager::ItemManager() :
    id_lookup(ItemDao::getItemDefinitions()),
    interactor_manager(new InteractorManager()) {

    std::map<std::string, std::string> interaction_types;

    for (auto furniture : this->id_lookup) {
        this->sprite_lookup[furniture.second->sprite_id] = furniture.second->id;
    }
}

/*
    Get item definitiion instance by item id

    @param item id
    @return item definition
*/
ItemDefinition *ItemManager::getDefinitionByID(int item_id) {

    if (this->id_lookup.count(item_id) > 0) {
        return this->id_lookup.find(item_id)->second;
    }

    return nullptr;
}

/*
    Get item definitiion instance by sprite id

    @param sprite id
    @return item definition
*/
ItemDefinition *ItemManager::getDefinitionBySpriteID(int item_id) {

    if (this->sprite_lookup.count(item_id) > 0) {
        return this->getDefinitionByID(sprite_lookup.find(item_id)->second);
    }

    return nullptr;
}

/*
    Item manager deconstructor
*/
ItemManager::~ItemManager() {
    delete this->interactor_manager;
}

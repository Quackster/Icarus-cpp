/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <vector>

#include "game/item/interactor/InteractorManager.h"
#include "game/item/definitions/ItemDefinition.h"

class ItemManager
{
public:
    ItemManager();
    ~ItemManager();

    ItemDefinition *getDefinitionByID(int item_id);
    ItemDefinition *getDefinitionBySpriteID(int item_id);

    InteractorManager *getInteractorManager() { return this->interactor_manager; }

private:
    std::map<int, ItemDefinition*> id_lookup;
    std::map<int, int> sprite_lookup;

    InteractorManager *interactor_manager;
};


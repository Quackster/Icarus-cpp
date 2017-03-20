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
#include "game/item/definitions/ItemDefinition.h"

class ItemManager
{
public:
    ItemManager();
    ~ItemManager();

    ItemDefinition *getDefinitionByID(int item_id);
    ItemDefinition *getDefinitionBySpriteID(int item_id);

private:
    std::map<int, ItemDefinition*> id_lookup;
    std::map<int, ItemDefinition*> sprite_lookup;
};


/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "misc/Utilities.h"

#include "game/room/Room.h"

#include "game/item/Item.h"
#include "game/item/definitions/ItemDefinition.h"
#include "game/item/interactor/BaseInteractor.h"

class DefaultInteractor : public BaseInteractor {

public:
    DefaultInteractor() { }

    void onInteract(Room *room, Item *item) {

        int modes = item->getDefinition()->interaction_modes_count;
        int current_mode = Utilities::isNumber(item->extra_data) ? stoi(item->extra_data) : 0;

        if (current_mode >= modes) {
            current_mode = 0;
        }
        else {
            current_mode++;
        }

        item->extra_data = std::to_string(current_mode);
        item->updateStatus();
        item->save();
    }
};
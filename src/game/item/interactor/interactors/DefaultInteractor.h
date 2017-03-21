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

        int current_mode = 0;
        int new_mode = 0;

        if (Utilities::isNumber(item->extra_data)) {
            current_mode = stoi(item->extra_data);
        }

        if (current_mode <= 0) {
            new_mode = 1;
        }
        else if (current_mode >= modes) {
            new_mode = 0;
        }
        else {
            new_mode = current_mode + 1;
        }

        if (new_mode == current_mode) {
            return; // don't bother updating since nothing changed
        }

        item->extra_data = std::to_string(new_mode);
        item->updateStatus();
        item->save();
    }
};
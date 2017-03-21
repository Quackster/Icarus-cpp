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

#include "boot/Icarus.h"
#include "game/room/Room.h"

#include "game/item/Item.h"
#include "game/item/definitions/ItemDefinition.h"
#include "game/item/interactor/BaseInteractor.h"

class GateInteractor : public BaseInteractor {

public:
    GateInteractor() { }

    void onInteract(Room *room, Item *item) {
        
        // Call default interactor, but here we need to re-do the collision map because 
        // it's a gate!

        BaseInteractor *default = Icarus::getGame()->getItemManager()->getInteractorManager()->getInteractor("default");
        default->onInteract(room, item);

        // Redo collision map to allow people to walk through, or block people!
        room->getDynamicModel()->regenerateCollisionMaps();
    }
};
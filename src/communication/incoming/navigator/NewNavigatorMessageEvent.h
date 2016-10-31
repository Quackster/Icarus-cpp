/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "boot/Icarus.h"
#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/navigator/FlatCategoriesMessageComposer.h"
#include "communication/outgoing/navigator/NavigatorCategoriesComposer.h"
#include "communication/outgoing/navigator/NavigatorMetaDataComposer.h"
#include "communication/outgoing/navigator/NavigatorPreferencesMessageComposer.h"

#include "communication/outgoing/user/CreditsMessageComposer.h"
#include "communication/outgoing/user/UserObjectMessageComposer.h"
#include "communication/outgoing/user/SendPerkAllowancesMessageComposer.h"

class NewNavigatorMessageEvent : public MessageEvent {

public:
    NewNavigatorMessageEvent() { }

    void handle(Player *player, Request &request) {

        player->send(FlatCategoriesMessageComposer(Icarus::getGame()->getNavigatorManager()->getCategories(), player->getDetails()->getRank()));
        player->send(NavigatorCategoriesComposer(Icarus::getGame()->getNavigatorManager()->getCategories()));
        player->send(NavigatorMetaDataComposer());
        player->send(NavigatorPreferencesMessageComposer());
    }
};
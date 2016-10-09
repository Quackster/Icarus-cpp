#pragma once
#include "boot/Icarus.h"
#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/navigator/FlatCategoriesMessageComposer.h"
#include "communication/outgoing/navigator/NavigatorCategoriesComposer.h"
#include "communication/outgoing/navigator/NavigatorMetaDataComposer.h"

#include "communication/outgoing/user/CreditsMessageComposer.h"
#include "communication/outgoing/user/UserObjectMessageComposer.h"
#include "communication/outgoing/user/SendPerkAllowancesMessageComposer.h"

class UserDataMessageEvent : public MessageEvent {

public:
    UserDataMessageEvent() { }

    void handle(Player *player, Request &request) {

        player->login();

        auto categories = Icarus::getGame()->getNavigatorManager()->getCategories();
        
        /*
        Enable new navigator
        */
        player->send(FlatCategoriesMessageComposer(categories, player->getDetails()->getRank()));
        player->send(NavigatorCategoriesComposer(categories));
        player->send(NavigatorMetaDataComposer());

        /*
        Send user data
        */
        player->send(CreditsMessageComposer(player->getDetails()->getCredits()));
        player->send(UserObjectMessageComposer(player));
        player->send(SendPerkAllowancesMessageComposer());
    }
};
#pragma once
#include "boot/Icarus.h"
#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/navigator/FlatCategoriesMessageComposer.h"
#include "communication/outgoing/navigator/NavigatorCategoriesComposer.h"
#include "communication/outgoing/navigator/NavigatorMetaDataComposer.h"

class NewNavigatorMessageEvent : public MessageEvent {

public:
    NewNavigatorMessageEvent() { }

    void handle(Player *player, Request request) {

        auto categories = Icarus::getGame()->getNavigatorManager()->getCategories();
        
        player->send(FlatCategoriesMessageComposer(categories, player->getDetails()->getRank()));
        player->send(NavigatorCategoriesComposer(categories));
        player->send(NavigatorMetaDataComposer());
    }
};
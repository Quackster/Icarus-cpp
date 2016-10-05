#pragma once
#include "boot/Icarus.h"
#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/navigator/FlatCategoriesMessageComposer.h"
#include "communication/outgoing/navigator/NavigatorCategoriesComposer.h"
#include "communication/outgoing/navigator/NavigatorMetaDataComposer.h"

class NewNavigatorMessageEvent : public MessageEvent {

public:
    NewNavigatorMessageEvent() { }

    void handle(Session *session, Request request) {

        auto categories = Icarus::getGame()->getNavigatorManager()->getCategories();
        
        session->send(FlatCategoriesMessageComposer(categories, session->getDetails()->getRank()));
        session->send(NavigatorCategoriesComposer(categories));
        session->send(NavigatorMetaDataComposer());



    }
};
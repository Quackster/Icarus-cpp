#pragma once
#include "boot/Icarus.h"
#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/navigator/FlatCategoriesMessageComposer.h"

class NewNavigatorMessageEvent : public MessageEvent {

public:
    NewNavigatorMessageEvent() { }

    void handle(Session *session, Request request) {

        session->send(FlatCategoriesMessageComposer(Icarus::getGame()->getNavigatorManager()->getCategories(), session->getSessionDetails()->getRank()));

    }
};
#pragma once
#include "boot/Icarus.h"
#include "game/navigator/NavigatorTab.h"
#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/navigator/SearchResultSetComposer.h"

class SearchNewNavigatorEvent : public MessageEvent {

public:
    SearchNewNavigatorEvent() { }

    void handle(Session *session, Request request) {

        string tab = request.readString();
        string query = request.readString();

        NavigatorTab *navigator_tab = Icarus::getGame()->getNavigatorManager()->getTab(tab);

        if (navigator_tab == nullptr) {
            return;
        }

        session->send(SearchResultSetComposer(session, navigator_tab, query));
    }
};
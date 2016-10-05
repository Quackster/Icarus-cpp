#pragma once
#pragma once
#include "communication/incoming/MessageEvent.h"

class NewNavigatorMessageEvent : public MessageEvent {

public:
    NewNavigatorMessageEvent() { }

    void handle(Session *session, Request request) {

        cout << "topkek";

    }
};
#pragma once
#pragma once
#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/login/AuthenticateMessageComposer.h"
#include "communication/outgoing/login/UniqueMachineIDMessageComposer.h"
#include "communication/outgoing/login/HomeRoomMessageComposer.h"
#include "communication/outgoing/login/LandingWidgetMessageComposer.h"


#include "dao/UserDao.h"

class AuthenticateMessageEvent : public MessageEvent {

public:
    AuthenticateMessageEvent() { }

    void handle(Session *session, Request request) {

        SessionDetails *details = UserDao::findUserByTicket(session, request.readString());

        if (details == nullptr) {
            session->getNetworkConnection()->getSocket().close();
            return;
        }
        else {
            session->setSessionDetails(details);
        }

        session->send(AuthenticateMessageComposer());
        session->send(UniqueMachineIDMessageComposer(session->getUniqueId()));
        session->send(HomeRoomMessageComposer(0, false));
        session->send(LandingWidgetMessageComposer());
    }
};
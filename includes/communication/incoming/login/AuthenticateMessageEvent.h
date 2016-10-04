#pragma once
#pragma once
#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/login/AuthenticateMessageComposer.h"

#include "dao/UserDao.h"

class AuthenticateMessageEvent : public MessageEvent {

public:
    AuthenticateMessageEvent() { }

    void handle(Session *session, Request request) {

        SessionDetails *details = UserDao::findUserByTicket(session, request.readString());

        // Can't find user? Close their damn connection! :)
        if (details != nullptr) {
            session->getNetworkConnection()->getSocket().close();
            return;
        }
        else {
            session->setSessionDetails(details);
        }

        session->send(new AuthenticateMessageComposer());

        Response response = Response(1351);
        response.writeString("");
        response.writeString("");
        session->getNetworkConnection()->send(response);

        response = Response(704);
        response.writeInt(0);
        response.writeInt(0);
        session->getNetworkConnection()->send(response);
    }
};
/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
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

    void handle(Player *session, Request &request) {

        PlayerDetails *details = UserDao::findUserByTicket(session, request.readString());

        if (details == nullptr) {
            session->getNetworkConnection()->getSocket().close();
            return;
        }
        else {
            session->setDetails(details);
        }

        session->send(AuthenticateMessageComposer());
        session->send(UniqueMachineIDMessageComposer(session->getUniqueId()));
        session->send(HomeRoomMessageComposer(0, false));
        session->send(LandingWidgetMessageComposer());
    }
};
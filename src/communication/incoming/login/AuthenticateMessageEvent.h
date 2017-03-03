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

#include "plugin/events/player/PlayerLoginEvent.h"
#include "plugin/events/Event.h"

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

        std::string sso_ticket = request.readString();

        if (!UserDao::exists(sso_ticket)) {
            session->getNetworkConnection()->getSocket().close();
            return;
        }
		else {

			EntityDetails *details = UserDao::findUserByTicket(session, sso_ticket);

			if (Icarus::getPlayerManager()->getPlayersIDLookup()->count(details->id) > 0) {
				session->getNetworkConnection()->getSocket().close();
				delete details;
				return;
			}

			session->setDetails(details);
		}

        session->send(AuthenticateMessageComposer());
        session->send(UniqueMachineIDMessageComposer(""));// session->getUniqueId()));
        session->send(HomeRoomMessageComposer(0, false));
        session->send(LandingWidgetMessageComposer());

		PlayerLoginEvent *event = static_cast<PlayerLoginEvent*>(Icarus::getGame()->getPluginManager()->callEvent(std::make_shared<PlayerLoginEvent>(*session, sso_ticket)));

		if (event->isCancelled()) {
			return;
		}

        session->login();

        //[0][0][0][10]D[0][12]bonusbag16_2[0][0]#"[0][0][0]x[0][0][0]x
        Response response(266);
        response.writeString("A2 DIGITV"); // product data id
        response.writeInt(2); // -1 for invisible
        response.writeInt(3); // amount
        response.writeInt(4); // max amount
        session->getNetworkConnection()->send(response);
    }
};
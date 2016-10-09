#pragma once
#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/login/AuthenticateMessageComposer.h"

#include "dao/UserDao.h"

class VersionCheckMessageEvent : public MessageEvent {

public:
    VersionCheckMessageEvent() { }

    void handle(Player *player, Request request) {

        std::string revision = request.readString();

        if (revision != "PRODUCTION-201512012203-525044429") {
            player->getNetworkConnection()->getSocket().close();
        }
    }
};
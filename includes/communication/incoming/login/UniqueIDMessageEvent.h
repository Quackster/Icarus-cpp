#pragma once
#include "communication/incoming/MessageEvent.h"
#include "communication/outgoing/login/AuthenticateMessageComposer.h"

#include "dao/UserDao.h"

class UniqueIDMessageEvent : public MessageEvent {

public:
    UniqueIDMessageEvent() { }

    void handle(Player *player, Request request) {
        player->setUniqueId(request.readString());
    }
};
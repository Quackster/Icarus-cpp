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

#include "communication/outgoing/room/doorbell/GenericNoAnswerDoorbellMessageComposer.h"
#include "communication/outgoing/room/doorbell/AcceptUserInsideRoomMessageComposer.h"
#include "communication/outgoing/user/HotelViewMessageComposer.h"

#include "communication/incoming/MessageEvent.h"

class AnswerDoorbellMessageEvent : public MessageEvent {

public:
    AnswerDoorbellMessageEvent() { }

    void handle(Player *player, Request &request) {

        Room *room = player->getRoomUser()->getRoom();

        if (room == nullptr) {
            return;
        }

        std::string name = request.readString();
        bool accept = request.readBool();

        if (name.length() < 1) {
            return;
        }

        Player *client = Icarus::getPlayerManager()->getPlayerByUsername(name);

        if (client == nullptr) {
            return;
        }

        if (!client->authenticated()) {
            return;
        }

        if (!accept) {
            client->send(GenericNoAnswerDoorbellMessageComposer());
            
            if (player->getRoomUser()->inRoom()) {
                player->getRoomUser()->getRoom()->leave(player, true);
            }
        }
        else {
            client->send(AcceptUserInsideRoomMessageComposer());
        }

    }
};
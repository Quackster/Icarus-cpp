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

#include "communication/outgoing/navigator/CanCreateRoomMessageComposer.h"
#include "communication/outgoing/navigator/CreateRoomMessageComposer.h"

#include "dao/NavigatorDao.h"

class CreateRoomMessageEvent : public MessageEvent {

public:
    CreateRoomMessageEvent() { }

    void handle(Player *player, Request &request) {

        // [3]<[0]
        //[10]tewqdwqdwq[0][4]dwwd[0][7]model_a
        
        //[0][0][0][9]
        //[0][0][0][0][0][0][2]

        std::string room_name = request.readString();
        std::string description = request.readString();
        std::string room_model = request.readString();

        if (room_name.length() < 1) {
            return;
        }

        if (room_model.length() < 1) {
            return;
        }

        int category = request.readInt();
        int max_users = request.readInt();
        int trade_settings = request.readInt();


		if (player->getRooms().size() >= Icarus::getGame()->MAX_ROOMS_PER_ACCOUNT) {
			player->send(CanCreateRoomMessageComposer(player));
			return;
		}

		int id = NavigatorDao::createRoom(room_name, description, room_model, player->getDetails()->getId(), category, max_users, trade_settings);

		player->send(CreateRoomMessageComposer(id, room_name));

    }
};
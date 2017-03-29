/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <sstream>

#include "communication/incoming/MessageEvent.h"

#include "communication/outgoing/room/doorbell/GenericDoorbellMessageComposer.h"
#include "communication/outgoing/room/doorbell/GenericErrorMessageComposer.h"
#include "communication/outgoing/room/doorbell/GenericNoAnswerDoorbellMessageComposer.h"
#include "communication/outgoing/room/doorbell/RoomEnterErrorMessageComposer.h"
#include "communication/outgoing/user/HotelViewMessageComposer.h"

class EnterRoomMessageEvent : public MessageEvent {

public:
    EnterRoomMessageEvent() { }

    void handle(Player *player, Request &request) {

        int room_id = request.readInt();

        player->getRoomUser()->leaveRoom(false);

        Room *room = Icarus::getGame()->getRoomManager()->getRoom(room_id);

        if (room == nullptr) {

            room = RoomDao::getRoom(room_id);

            if (room != nullptr) {
                Icarus::getGame()->getRoomManager()->addRoom(room);
            }
            else {
                return;
            }
        }

        if (room->getData()->users_now >= room->getData()->users_max) {

            if (!player->hasFuse("user_enter_full_rooms") && room->getData()->owner_id != player->getDetails()->id) {
                player->send(RoomEnterErrorMessageComposer(1));
                player->send(HotelViewMessageComposer());
                return;
            }
        }

        if (room->getData()->state > 0 && !room->hasRights(player, false)) {
            if (room->getData()->state == RoomState::DOORBELL) {

                if (room->getData()->users_now > 0) {

                    // Send to all users who have rights in that particular room
                    room->send(GenericDoorbellMessageComposer(player->getDetails()->username), true);

                    // Tell user we're ringing doorbell
                    player->send(GenericDoorbellMessageComposer(1));
                }
                else {
                    player->send(GenericNoAnswerDoorbellMessageComposer());
                    player->send(HotelViewMessageComposer());
                }

                return;
            }

            if (room->getData()->state == RoomState::PASSWORD) {

                std::string password = request.readString();

                if (password != room->getData()->password) {
                    player->send(GenericErrorMessageComposer(-100002));
                    player->send(HotelViewMessageComposer());
                    return;
                }
            }
        }

        std::stringstream ss;
        ss << "/client/private/";
        ss << std::to_string(room->id);
        ss << "/id";

        Response response(166);
        response.writeString(ss.str());
        player->getNetworkConnection()->send(response);

        room->enter(player); // call method to finalise enter room
    }
};
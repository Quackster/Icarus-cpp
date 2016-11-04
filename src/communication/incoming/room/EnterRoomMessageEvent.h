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

        if (player->getRoomUser()->getRoom() != nullptr) {
            player->getRoomUser()->getRoom()->leave(player, false);// , !(player->getRoomUser()->getRoom()->getId() == room_id));
        }

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

        if (room->getPlayers().size() >= room->getData()->users_max) {

            if (!player->hasFuse("user_enter_full_rooms") && !room->getData()->owner_id != player->getDetails()->id) {
                player->send(RoomEnterErrorMessageComposer(1));
                player->send(HotelViewMessageComposer());
                return;
            }
        }

        if (room->getData()->state > 0 && !room->hasRights(player->getDetails()->id, false)) {
            if (room->getData()->room_state == ROOM_STATE_DOORBELL) {

                if (room->getPlayers().size() > 0) {

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

            if (room->getData()->room_state == ROOM_STATE_PASSWORD) {

                player->send(GenericErrorMessageComposer(-100002));
                player->send(HotelViewMessageComposer());
                return;
            }
        }

        room->enter(player); // call method to finalise enter room
    }
};
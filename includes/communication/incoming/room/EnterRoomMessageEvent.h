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

#include "communication/outgoing/room/entry/RoomRatingMessageComposer.h"
#include "communication/outgoing/room/entry/RoomModelMessageComposer.h"
#include "communication/outgoing/room/entry/RoomSpacesMessageComposer.h"
#include "communication/outgoing/room/entry/RoomOwnerMessageComposer.h"
#include "communication/outgoing/room/entry/RightsLevelMessageComposer.h"
#include "communication/outgoing/room/entry/NoRightsMessageComposer.h"
#include "communication/outgoing/room/entry/PrepareRoomMessageComposer.h"

class EnterRoomMessageEvent : public MessageEvent {

public:
    EnterRoomMessageEvent() { }

    void handle(Player *player, Request &request) {

        int room_id = request.readInt();

        Room *room = Icarus::getGame()->getRoomManager()->getRoom(room_id);

        if (room == nullptr) {
            return;
        }

        if (player->getRoomUser()->getRoom() != nullptr) {
            player->getRoomUser()->getRoom()->leave(player, false);
        }

        RoomData *room_data = room->getData();

        // So we don't forget what room we entered 8-)
        player->getRoomUser()->setRoom(room);
        player->getRoomUser()->setLoadingRoom(true);
        player->getRoomUser()->setVirtualId(room->getData()->getVirtualId());

        player->send(RoomModelMessageComposer(room_data->getModel()->getName(), room_id));
        player->send(RoomRatingMessageComposer(room_data->getScore()));

        std::string floor = room_data->getFloor();
        std::string wall = room_data->getWallpaper();

        if (floor.length() > 0) {
            player->send(RoomSpacesMessageComposer("floor", floor));
        }

        if (wall.length() > 0) {
            player->send(RoomSpacesMessageComposer("wall", floor));
        }

        player->send(RoomSpacesMessageComposer("landscape", room_data->getOutside()));

        if (room->hasRights(player->getDetails()->getId(), true)) {
            player->getRoomUser()->updateStatus("flatctrl", "useradmin");
            player->send(RoomOwnerMessageComposer());
            player->send(RightsLevelMessageComposer(4)); 
        }
        else if (room->hasRights(player->getDetails()->getId(), false)) {
            player->getRoomUser()->updateStatus("flatctrl", "1");
            player->send(RightsLevelMessageComposer(1));
        }

        player->send(PrepareRoomMessageComposer(room_id));

        /* if  self.has_rights(session.details.id, True):

            session.room_user.statuses["flatctrl"] = "useradmin"
            session.send(YouAreOwnerComposer())
            session.send(RightsLevelMessageComposer(4))

        elif self.has_rights(session.details.id, False):

            session.room_user.statuses["flatctrl"] = "1"
            session.send(RightsLevelMessageComposer(1))
        else:
            session.send(NoRightsMessageComposer())*/


    }
};
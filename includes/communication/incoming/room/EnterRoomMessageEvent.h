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

        room->getEntities()->push_back(player);

        RoomData *room_data = room->getData();

        // So we don't forget what room we entered 8-)
        player->getRoomUser()->setRoom(room);

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

        player->send(RoomOwnerMessageComposer());
        player->send(RightsLevelMessageComposer(4));

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
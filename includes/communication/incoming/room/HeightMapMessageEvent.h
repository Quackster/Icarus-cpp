#pragma once
#include "communication/incoming/MessageEvent.h"

#include "communication/outgoing/room/model/FloorMapMessageComposer.h"
#include "communication/outgoing/room/model/HeightMapMessageComposer.h"

#include "communication/outgoing/room/UserDisplayMessageComposer.h"
#include "communication/outgoing/room/UserStatusMessageComposer.h"

class HeightMapMessageEvent : public MessageEvent {

public:
    HeightMapMessageEvent() { }

    void handle(Player *player, Request &request) {

        Room *room = player->getRoomUser()->getRoom();

        if (room == nullptr) {
            return;
        }

        player->send(HeightMapMessageComposer(room));
        player->send(FloorMapMessageComposer(room));
        
        player->getRoomUser()->setLoadingRoom(false);

        RoomModel *model = room->getData()->getModel();
        RoomUser *room_user = player->getRoomUser();

        room_user->setX(model->getDoorX());
        room_user->setY(model->getDoorY());
        room_user->setHeight(model->getDoorZ());
        room_user->setRotation(model->getDoorRotation(), true);

        player->send(UserDisplayMessageComposer(player));
        player->send(UserStatusMessageComposer(player));
    }
};
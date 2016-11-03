/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "game/room/Room.h"
#include <string>

#include "communication/outgoing/MessageComposer.h"

class RoomSettingsDataMessageComposer : public MessageComposer {

public:
    RoomSettingsDataMessageComposer(Room *room) :
        room(room) { }

    const Response compose() const {

        RoomData *room_data = room->getData();

        Response response = this->createResponse();
        response.writeInt(room_data->getId());
        response.writeString(room_data->getName());
        response.writeString(room_data->getDescription());
        response.writeInt(room_data->getState());
        response.writeInt(room_data->getCategory());
        response.writeInt(room_data->getUsersMax());
        response.writeInt(room_data->getUsersMax());
        response.writeInt(room_data->getTags().size());
        
        for (auto tag : room_data->getTags()) {
            response.writeString(tag);
        }

        response.writeInt(room_data->getTradeState());
        response.writeInt(room_data->hasAllowPets());
        response.writeInt(room_data->hasAllowPetsEat());
        response.writeInt(room_data->hasAllowWalkthrough());
        response.writeInt(room_data->hasHideWall());
        response.writeInt(room_data->getWallThickness());
        response.writeInt(room_data->getFloorThickness());
        response.writeInt(room_data->getChatSpeed());
        response.writeInt(room_data->getChatSize());
        response.writeInt(room_data->getChatSpeed());
        response.writeInt(room_data->getChatDistance());
        response.writeInt(room_data->getChatFlood());
        response.writeBool(false);
        response.writeInt(room_data->getWhoCanMute());
        response.writeInt(room_data->getWhoCanKick());
        response.writeInt(room_data->getWhoCanBan());

        return response;
    }

    const int getHeader() const {
        return Outgoing::RoomSettingsDataMessageComposer;
    }

private:
    Room *room;
};
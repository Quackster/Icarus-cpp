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
        response.writeInt(room_data->id);
        response.writeString(room_data->name);
        response.writeString(room_data->description);
        response.writeInt(room_data->state);
        response.writeInt(room_data->category);
        response.writeInt(room_data->users_max);
        response.writeInt(room_data->users_max);
        response.writeInt(room_data->tags.size());
        
        for (auto tag : room_data->tags) {
            response.writeString(tag);
        }

        response.writeInt(room_data->trade_state);
        response.writeInt(room_data->allow_pets);
        response.writeInt(room_data->allow_pets_eat);
        response.writeInt(room_data->allow_walkthrough);
        response.writeInt(room_data->hide_wall);
        response.writeInt(room_data->wall_thickness);
        response.writeInt(room_data->floor_thickness);
        response.writeInt(room_data->chat_speed);
        response.writeInt(room_data->chat_size);
        response.writeInt(room_data->chat_speed);
        response.writeInt(room_data->chat_distance);
        response.writeInt(room_data->chat_flood);
        response.writeBool(true);
        response.writeInt(room_data->who_can_mute);
        response.writeInt(room_data->who_can_kick);
        response.writeInt(room_data->who_can_ban);

        return response;
    }

    const int getHeader() const {
        return Outgoing::RoomSettingsDataMessageComposer;
    }

private:
    Room *room;
};
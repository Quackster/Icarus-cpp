/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include "misc/Utilities.h"

#include "communication/outgoing/room/RoomDataMessageComposer.h"
#include "communication/incoming/MessageEvent.h"

class SaveRoomMessageEvent : public MessageEvent {

public:
    SaveRoomMessageEvent() { }

    void handle(Player *player, Request &request) {

        // TODO: Move this variable elsewhere
        int MAX_ROOM_NAME_LENGTH = 50;

        Room *room = Icarus::getGame()->getRoomManager()->getRoom(request.readInt());

        if (room == nullptr) {
            return;
        }

        if (!room->hasRights(player, true)) {
            return;
        }

        RoomData *room_data = room->getData();

        std::string room_name = request.readString();
        room_name = Utilities::escape(room_name);

        std::string description = request.readString();
        description = Utilities::escape(description, true);

        int access_type = request.readInt();
       
        std::string password = request.readString();
        password = Utilities::escape(password);

        int max_users = request.readInt();
        int category_id = request.readInt();
        int tag_size = request.readInt();

        if (tag_size > 2) {
            return; 
        }

        std::vector<std::string> tags;

        for (int i = 0; i < tag_size; i++) {

            std::string new_tag = request.readString();
            new_tag = Utilities::escape(new_tag, false, true);

            if (new_tag.length() > 0) {
                tags.push_back(new_tag);
            }
        }

        int trade_settings = request.readInt();
        int allow_pets = request.readInt();
        int allow_pets_eat = request.readInt();
        int allow_walkthrough = request.readInt();

        int hide_wall = request.readInt();
        int wall_thickness = request.readInt();
        int floor_thickness = request.readInt();

        int who_can_mute = request.readInt();
        int who_can_kick = request.readInt();
        int who_can_ban = request.readInt();

        int chat_mode = request.readInt();
        int chat_size = request.readInt();
        int chat_speed = request.readInt();
        int chat_distance = request.readInt();
        int chat_flood = request.readInt();

        if (chat_mode != 1) {
            chat_mode = 0;
        }

        if (chat_size != 1) {
            chat_size = 0;
        }

        if (chat_speed != 1) {
            chat_speed = 0;
        }

        if (chat_distance > 100 || chat_distance < 0) {
            chat_distance = 1;
        }

        if (chat_flood < 0 || chat_flood > 2) {
            chat_flood = 1;
        }

        if (trade_settings < 0 || trade_settings > 2) {
            trade_settings = 1;
        }

        if (who_can_mute != 1) {
            who_can_mute = 0;
        }

        if (who_can_kick != 1) {
            who_can_kick = 0;
        }

        if (who_can_ban != 1) {
            who_can_ban = 0;
        }

        if (room_name.length() < 2) {
            return;
        }

        if (room_name.length() > MAX_ROOM_NAME_LENGTH) {
            room_name = room_name.substr(MAX_ROOM_NAME_LENGTH);
        }

        NavigatorCategory *category = Icarus::getGame()->getNavigatorManager()->getCategoryById(category_id);

        if (category == nullptr) {
            category_id = 1; // Category ID 1: No Category
        }

        room_data->name = room_name;
        room_data->description = description;
        room_data->state = access_type;
        room_data->users_max = max_users;
        room_data->password = password;
        room_data->category = category_id;
        room_data->tags = tags;
        room_data->trade_state = trade_settings;
        room_data->allow_pets = allow_pets;
        room_data->allow_pets_eat = allow_pets_eat;
        room_data->allow_walkthrough = allow_walkthrough;
        room_data->hide_wall = hide_wall;
        room_data->wall_thickness = wall_thickness;
        room_data->floor_thickness = floor_thickness;
        room_data->who_can_mute = who_can_mute;
        room_data->who_can_kick = who_can_kick;
        room_data->who_can_ban = who_can_ban;
        room_data->chat_mode = chat_mode;
        room_data->chat_size = chat_size;
        room_data->chat_speed = chat_speed;
        room_data->chat_distance = chat_distance;
        room_data->chat_flood = chat_flood;
        room->save();

        room->send(RoomDataMessageComposer(room, player, false, false));
    }
};
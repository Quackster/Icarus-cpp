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

class SaveRoomMessageEvent : public MessageEvent {

public:
    SaveRoomMessageEvent() { }

    void handle(Player *player, Request &request) {

        // TODO: Move this variable elsewhere
        int MAX_ROOM_NAME_LENGTH = 50;

        if (!player->getRoomUser()->inRoom()) {
            return;
        }

        Room *room = player->getRoomUser()->getRoom();

        if (!room->hasRights(player->getDetails()->getId(), true)) {
            return;
        }

        std::string room_name = request.readString();
        std::string description = request.readString();
        int access_type = request.readInt();
        int max_users = request.readInt();
        int category_id = request.readInt();
        int tag_size = request.readInt();

        std::vector<std::string> tags;

        for (int i = 0; i < tag_size; i++) {
            tags.push_back(request.readString());
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
        int trade_settings = request.readInt();

        if (chat_mode < 0 || chat_mode > 1) {
            return;
        }

        if (chat_size < 0 || chat_size > 1) {
            return;
        }

        if (chat_speed < 0 || chat_speed > 1) {
            return;
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

        if (who_can_mute < 0 || who_can_mute > 1) {
            who_can_mute = 0;
        }

        if (who_can_kick < 0 || who_can_kick > 1) {
            who_can_kick = 0;
        }

        if (who_can_ban < 0 || who_can_ban > 1) {
            who_can_ban = 0;
        }

        if (room_name.length < 2) {
            return;
        }

        if (room_name.length() > MAX_ROOM_NAME_LENGTH) {
            room_name = room_name.substr(MAX_ROOM_NAME_LENGTH);
        }

        NavigatorCategory *category = Icarus::getGame()->getNavigatorManager()->getCategoryById(category_id);

        if (category == nullptr) {
            category_id = 1; // Category ID 1: No Category
        }

        if (tag_size > 2) {
            return; // definitely scripting if try to put more than 2 tags...
        }


    }
};
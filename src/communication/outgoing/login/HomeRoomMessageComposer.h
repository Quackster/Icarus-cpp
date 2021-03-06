/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include "communication/outgoing/MessageComposer.h"

class HomeRoomMessageComposer : public MessageComposer {

public:
    HomeRoomMessageComposer(int room_id, bool force_enter) :
        room_id(room_id), 
        force_enter(force_enter) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(room_id);
        response.writeInt(force_enter);
        return response;
    }

    const int getHeader() const {
        return Outgoing::HomeRoomMessageComposer;
    }
private:
    int room_id;
    bool force_enter;
};
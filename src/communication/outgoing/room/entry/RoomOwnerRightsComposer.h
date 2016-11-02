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

class RoomOwnerRightsComposer : public MessageComposer {

public:
    RoomOwnerRightsComposer(int user_id, bool has_rights) : 
        user_id(user_id), 
        has_rights(has_rights) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->user_id);
        response.writeBool(this->has_rights);
        return response;
    }

    const int getHeader() const {
        return Outgoing::RoomOwnerRightsComposer;
    }

private:
    int user_id;
    bool has_rights;
};
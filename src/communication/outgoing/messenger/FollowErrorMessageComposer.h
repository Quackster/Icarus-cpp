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

class FollowErrorMessageComposer : public MessageComposer {

public:
    FollowErrorMessageComposer(int error_id) :
        error_id(error_id) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(this->error_id);
        return response;
    }

    const int getHeader() const {
        return Outgoing::FollowErrorMessageComposer;
    }

private:
    int error_id;
};
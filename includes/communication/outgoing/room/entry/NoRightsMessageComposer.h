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
#include "game/player/Player.h"

#include "communication/outgoing/MessageComposer.h"

class NoRightsMessageComposer : public MessageComposer {

public:
    NoRightsMessageComposer() { }

    Response compose() {
        Response response = this->createResponse();
        return response;
    }

    int getHeader() {
        return Outgoing::YouAreNotControllerMessageComposer;
    }

};
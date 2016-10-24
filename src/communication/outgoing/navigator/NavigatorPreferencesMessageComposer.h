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

class NavigatorPreferencesMessageComposer : public MessageComposer {

public:
	NavigatorPreferencesMessageComposer() { }

    const Response compose() const {
        Response response = this->createResponse();
		response.writeInt(68);
		response.writeInt(42);
		response.writeInt(425);
		response.writeInt(535);
		response.writeBool(false);
		response.writeInt(0);
        return response;
    }

    const int getHeader() const {
        return Outgoing::NavigatorPreferencesMessageComposer;
    }
};
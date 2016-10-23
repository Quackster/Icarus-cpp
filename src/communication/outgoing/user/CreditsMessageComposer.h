/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <string>

#include "communication/outgoing/MessageComposer.h"

class CreditsMessageComposer : public MessageComposer {

public:
    CreditsMessageComposer(int credits) : credits(credits) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeString(std::to_string(credits));
        return response;
    }

    const int getHeader() const {
        return Outgoing::CreditsMessageComposer;
    }

private:
    int credits;

};
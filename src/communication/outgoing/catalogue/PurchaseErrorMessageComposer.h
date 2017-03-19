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

class PurchaseErrorMessageComposer : public MessageComposer {

public:
    PurchaseErrorMessageComposer(bool credits_error, bool pixel_error) :
        credits_error(credits_error),
        pixel_error(pixel_error) { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeBool(this->credits_error);
        response.writeBool(this->pixel_error);
        return response;
    }

    const int getHeader() const {
        return Outgoing::PurchaseErrorMessageComposer;
    }

private:
    bool credits_error;
    bool pixel_error;
};
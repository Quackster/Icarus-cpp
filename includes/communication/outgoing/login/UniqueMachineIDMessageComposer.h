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

class UniqueMachineIDMessageComposer : public MessageComposer {

public:
    UniqueMachineIDMessageComposer(std::string machine_id) :
        machine_id(machine_id) { }

    Response compose() {
        Response response = this->createResponse();
        response.writeString(machine_id);
        return response;
    }

    int getHeader() {
        return Outgoing::UniqueMachineIDMessageComposer;
    }

private:
    std::string machine_id;
};
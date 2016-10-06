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
#pragma once
#include "communication/outgoing/MessageComposer.h"

class UniqueMachineIDMessageComposer : public MessageComposer {

public:
    UniqueMachineIDMessageComposer(string machine_id) :
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
    string machine_id;
};
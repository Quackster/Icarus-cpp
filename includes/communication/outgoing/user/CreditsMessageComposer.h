#pragma once
#include <string>

#include "communication/outgoing/MessageComposer.h"

class CreditsMessageComposer : public MessageComposer {

public:
    CreditsMessageComposer(int credts) : credits(credits) { }

    Response compose() {
        Response response = this->createResponse();
        response.writeString(std::to_string(credits));
        return response;
    }

    int getHeader() {
        return Outgoing::CreditsMessageComposer;
    }

private:
    int credits;

};
#pragma once
#include "communication/outgoing/MessageComposer.h"

class HomeRoomMessageComposer : public MessageComposer {

public:
    HomeRoomMessageComposer(int room_id, bool force_enter) :
        room_id(room_id), force_enter(force_enter) { }

    Response compose() {
        Response response = this->createResponse();
        response.writeInt(room_id);
        response.writeInt(force_enter);
        return response;
    }

    int getHeader() {
        return Outgoing::HomeRoomMessageComposer;
    }
private:
    int room_id;
    bool force_enter;
};
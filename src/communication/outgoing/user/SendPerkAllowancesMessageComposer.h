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

class SendPerkAllowancesMessageComposer : public MessageComposer {

public:
    SendPerkAllowancesMessageComposer() { }

    const Response compose() const {
        Response response = this->createResponse();
        response.writeInt(15);
        response.writeString("USE_GUIDE_TOOL");
        response.writeString("");
        response.writeBool(false);
        response.writeString("GIVE_GUIDE_TOURS");
        response.writeString("requirement.unfulfilled.helper_le");
        response.writeBool(false);
        response.writeString("JUDGE_CHAT_REVIEWS");
        response.writeString(""); // ??
        response.writeBool(true);
        response.writeString("VOTE_IN_COMPETITIONS");
        response.writeString(""); // ??
        response.writeBool(true);
        response.writeString("CALL_ON_HELPERS");
        response.writeString(""); // ??
        response.writeBool(false);
        response.writeString("CITIZEN");
        response.writeString(""); // ??
        response.writeBool(true);
        response.writeString("TRADE");
        response.writeString(""); // ??
        response.writeBool(true);
        response.writeString("HEIGHTMAP_EDITOR_BETA");
        response.writeString(""); // ??
        response.writeBool(false);
        response.writeString("EXPERIMENTAL_CHAT_BETA");
        response.writeString("requirement.unfulfilled.helper_level_2");
        response.writeBool(true);
        response.writeString("EXPERIMENTAL_TOOLBAR");
        response.writeString(""); // ??
        response.writeBool(true);
        response.writeString("BUILDER_AT_WORK");
        response.writeString(""); // ??
        response.writeBool(true);
        response.writeString("NAVIGATOR_PHASE_ONE_2014");
        response.writeString(""); // ??
        response.writeBool(false);
        response.writeString("CAMERA");
        response.writeString(""); // ??
        response.writeBool(false);
        response.writeString("NAVIGATOR_PHASE_TWO_2014");
        response.writeString(""); // ??
        response.writeBool(true);
        response.writeString("MOUSE_ZOOM");
        response.writeString(""); // ??
        response.writeBool(true);
        response.writeString("NAVIGATOR_ROOM_THUMBNAIL_CAMERA");
        response.writeString(""); // ??
        response.writeBool(false);
        return response;
    }

    const int getHeader() const {
        return Outgoing::SendPerkAllowancesMessageComposer;
    }


};
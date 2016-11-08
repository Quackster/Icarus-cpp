/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <map>

#include "communication/incoming/MessageEvent.h"

class MessageHandler
{

private:
    std::map<int, MessageEvent*> messages;

public:
    MessageHandler();
    ~MessageHandler();
    MessageEvent *getMessageEvent(int header);
    void invoke(int header, Request &request, Player *player);
};


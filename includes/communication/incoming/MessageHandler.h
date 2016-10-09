#pragma once
#include <map>

#include "communication/incoming/MessageEvent.h"

class MessageHandler
{

private:
    std::map<int, MessageEvent*> *messages;

public:
    MessageHandler();
    ~MessageHandler();
    MessageEvent *getMessageEvent(int header);
    void createEvent(int header, MessageEvent *event);
    void invoke(int header, Request &request, Player *player);
};


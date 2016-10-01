#pragma once

#include "headers/Incoming.h"
#include "communication/streams/Request.h"

class IncomingMessage
{

public:
    virtual void read(Request request) = 0;
    virtual int getHeader() = 0;

};
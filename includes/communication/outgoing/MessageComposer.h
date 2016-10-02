#pragma once
//#include "headers/Incoming.h"
#include "headers/Outgoing.h"

#include "communication/streams/Request.h"
#include "communication/streams/Response.h"

class MessageComposer
{

public:
    virtual ~MessageComposer() {}
    virtual Response compose() = 0;
    virtual int getHeader() = 0;
    Response createResponse() { return Response(this->getHeader()); }
};
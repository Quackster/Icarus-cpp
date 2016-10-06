#pragma once
//#include "communication/headers/Incoming.h"
#include "communication/headers/Outgoing.h"

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
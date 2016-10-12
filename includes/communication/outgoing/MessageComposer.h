/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
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
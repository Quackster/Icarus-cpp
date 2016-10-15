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
    virtual const Response compose() const = 0;
    virtual const int getHeader() const = 0;
    const Response createResponse() const { return Response(this->getHeader()); }

};
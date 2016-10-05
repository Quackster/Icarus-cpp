#pragma once
#include "communication/outgoing/MessageComposer.h"


class Runnable
{

public:
    virtual ~Runnable() {}
    virtual void run() = 0;
};
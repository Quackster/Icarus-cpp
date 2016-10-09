#pragma once

#include "game/entities/EntityDetails.h"

class Entity
{

public:
    ~Entity() { }
    virtual EntityDetails *getDetails() = 0;
    virtual void setDetails(EntityDetails *details) = 0;

};
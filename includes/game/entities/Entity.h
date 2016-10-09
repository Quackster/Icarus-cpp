#pragma once

#include "game/entities/EntityDetails.h"
#include "game/entities/EntityType.h"

class Entity
{

public:
    ~Entity() { }
    virtual EntityDetails *getDetails() = 0;
    virtual void setDetails(EntityDetails *details) = 0;
    virtual EntityType getEntityType() = 0;

};
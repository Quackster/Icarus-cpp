#pragma once

#include <vector>

class Room;
class DisposablePopulator
{

public:
    virtual ~DisposablePopulator() {}
    virtual void dispose(std::vector<Room*> rooms) = 0;
};
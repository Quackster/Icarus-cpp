#pragma once
#include "NetworkConnection.h"

class Session 
{

public:
    Session(NetworkConnection *session_connection);
    ~Session();
    void clear();
    NetworkConnection *getNetworkConnection() { return networkConnection; }

private:
    NetworkConnection *networkConnection;

};
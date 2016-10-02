#pragma once
#include "network/NetworkConnection.h"

class Session
{

public:
    Session(NetworkConnection *networkConnection);
    ~Session();
    void send(MessageComposer *composer);
    void clear();

    NetworkConnection *getNetworkConnection() { return networkConnection; }

private:
    NetworkConnection *networkConnection;
    
};
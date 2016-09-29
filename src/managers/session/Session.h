#pragma once
#include "NetworkConnection.h"

class Session
{

public:
	Session(NetworkConnection *networkConnection);
	~Session();
	void clear();
    NetworkConnection *getNetworkConnection() { return networkConnection; }

private:
    NetworkConnection *networkConnection;
	
};
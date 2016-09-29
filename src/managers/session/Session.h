#pragma once
#include "NetworkConnection.h"

class Session
{

public:
	Session(std::shared_ptr<NetworkConnection> session_connection);
	~Session();
	void clear();
    std::shared_ptr<NetworkConnection> getNetworkConnection() { return networkConnection; }

private:
	std::shared_ptr<NetworkConnection> networkConnection;
	
};
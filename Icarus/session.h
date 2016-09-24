#pragma once
#include "NetworkConnection.h"

class Session {
public:
	Session(NetworkConnection *session_connection);
	~Session();
	void disconnected();

private:
	NetworkConnection *networkConnection;

public:
	NetworkConnection *getNetworkConnection() {
		return networkConnection;
	}
};
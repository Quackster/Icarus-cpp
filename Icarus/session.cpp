#include "stdafx.h"
#include "Session.h"
#include "Icarus.h"

Session::Session(NetworkConnection *networkConnection) : networkConnection(networkConnection) {
	printf("Created session for connection: %i\n", networkConnection->getConnectionId());
}

Session::~Session() {
	
	printf("Removed session for connection: %i\n", networkConnection->getConnectionId());

	// Dispose network connection
	Icarus::getNetworkServer()->removeNetworkConnection(this->networkConnection);
}

void Session::disconnected() {

	try {

		
	}
	catch (std::exception &e) {

		printf("Caught exception: %s\n", e.what());
	}
}

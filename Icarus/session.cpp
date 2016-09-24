#include "stdafx.h"
#include "Session.h"

Session::Session(NetworkConnection *session_connection) : networkConnection(session_connection) {
	
}

Session::~Session() {
}

void Session::disconnected() {

	/*try {
		
		printf("Client number %i disconnected\n", this->networkConnection->getConnectionId());
	}
	catch (std::exception &e) {

		printf("Caught exception: %s\n", e.what());
	}*/
}

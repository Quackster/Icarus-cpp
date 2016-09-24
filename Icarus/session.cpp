#include "stdafx.h"
#include "Session.h"

Session::Session(NetworkConnection *session_connection) : networkConnection(session_connection) {

}

Session::~Session() {
}

void Session::disconnected() {

	try {
		
		if (this->networkConnection != NULL) {
			printf("Client number %i disconnected\n", this->networkConnection->getConnectionId());
			//delete networkConnection;
		}
		else {
			printf("NETWORK CONNECTION IS NULL\n");
		}
	}
	catch (std::exception &e) {

		printf("Caught exception: %s\n", e.what());
	}
}

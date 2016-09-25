#include "stdafx.h"
#include "Session.h"
#include "Icarus.h"

Session::Session(NetworkConnection *session_connection) : networkConnection(session_connection) {

}

Session::~Session() {
}

void Session::disconnected() {

	try {

		Icarus::getNetworkServer()->removeNetworkConnection(this->networkConnection);
	}
	catch (std::exception &e) {

		printf("Caught exception: %s\n", e.what());
	}
}

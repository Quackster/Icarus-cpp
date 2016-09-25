#include "stdafx.h"
#include "Session.h"
#include "Icarus.h"

Session::Session(NetworkConnection *networkConnection) : networkConnection(networkConnection) {

}

Session::~Session() {
}

void Session::disconnected() {

	try {

		// Dispose network connection
		Icarus::getNetworkServer()->removeNetworkConnection(this->networkConnection);
	}
	catch (std::exception &e) {

		printf("Caught exception: %s\n", e.what());
	}
}

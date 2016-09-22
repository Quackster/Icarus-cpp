#include "stdafx.h"
#include "Session.h"

Session::Session(NetworkConnection session_connection) : networkConnection(session_connection) {

}

Session::~Session() {
}

void Session::disconnected() {
	printf("testing");
}

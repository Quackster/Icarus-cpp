#include "stdafx.h"
#include "Session.h"

Session::Session(std::shared_ptr<NetworkConnection> session_connection) : networkConnection(session_connection) {

}


Session::~Session()
{
}

void Session::clear() {

	printf("testing");
}

#include "stdafx.h"
#include "Session.h"

Session::Session(std::shared_ptr<SessionConnection> session_connection) : session_connection(session_connection) {

}


Session::~Session()
{
}

void Session::disconnected() {

	printf("testing");
}

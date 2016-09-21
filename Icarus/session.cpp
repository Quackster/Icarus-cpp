#include "stdafx.h"
#include "sessionConnection.h"
#include "session.h"

session::session(sessionConnection session_connection) : session_connection(session_connection) {

}


session::~session()
{
}

void session::disconnected() {

	printf("testing");
}

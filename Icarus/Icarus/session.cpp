#include "stdafx.h"
#include "sessionConnection.h"
#include "session.h"

session::session(sessionConnection session_connection) : session_connection(session_connection) {

	printf("testing");
}


session::~session()
{
}

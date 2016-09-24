#pragma once
#include "Session.h"

#include <iostream>
#include <map>

using namespace std;

class SessionManager {

	public:
		SessionManager();
		void addSession(Session *session, int connectionID);
		void removeSession(int connectionID);
		Session* getSession(int connectionID);

	private:
		map<int, Session*>* sessions;
};
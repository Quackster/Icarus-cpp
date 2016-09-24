#pragma once
#include "SessionManager.h"

class Icarus {

	public:
		
		static SessionManager sessionManager;
		static void boot();
		static void initialiseServer();
		static SessionManager getSessionManager() {
			return sessionManager;
		}
		
	private:
		
		Icarus() {}


};


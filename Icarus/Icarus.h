#pragma once
#include "Session.h"
#include "NetworkServer.h"

class Icarus
{
	public:
		NetworkServer server;
		static void boot();
		static void initialiseServer();
};


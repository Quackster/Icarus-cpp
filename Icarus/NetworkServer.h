#pragma once
#pragma comment(lib, "Ws2_32.lib")

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <winsock.h>

#include "NetworkServer.h"

class NetworkServer {

	public:
		NetworkServer();
		~NetworkServer();
		void startServer(int serverPort);
		void removeNetworkConnection(NetworkConnection *connection);

	private:
		int connectionID;
};

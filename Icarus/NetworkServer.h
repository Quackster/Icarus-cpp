#pragma once

#pragma comment(lib, "Ws2_32.lib")

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <winsock.h>

class NetworkServer {

	public:
		NetworkServer(short port);
		~NetworkServer();
		void startServer();

	private:
		int connectionID;
		short serverPort;
};

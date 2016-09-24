#pragma once

#pragma comment(lib, "Ws2_32.lib")

#include <stdlib.h>
#include <stdio.h>
#include <winsock.h>

// constructing vectors
#include <iostream>
#include <vector>
#include <sstream> 

using namespace std;

class NetworkConnection {

	public:
		NetworkConnection(int connectionID, SOCKET socket);
		~NetworkConnection();
		void write_data();
		void handle_data(char* data, int length);

		int getConnectionId() { return connectionID; }
		bool getConnectionState() { return connected; }
		void setConnectionState(bool state) { connected = state; }
		SOCKET getSocket() { return socket; };
		DWORD getThread() { return thread; }
		
	private:
		int connectionID;
		bool connected;
		SOCKET socket;
		DWORD thread;

		enum { max_length = 1024 };
		char data_read[max_length];
		char data_write[max_length];
};

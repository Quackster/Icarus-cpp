#include "stdafx.h"
#include "NetworkServer.h"

/*
	@source: http://www.rohitab.com/discuss/topic/26991-cc-how-to-code-a-multi-client-server-in-c-using-threads/
*/

NetworkServer::NetworkServer(short serverPort) 
	: serverPort(serverPort){

}

NetworkServer::~NetworkServer() {
}

void NetworkServer::startServer() {

	SOCKET sock;
	DWORD thread;

	WSADATA wsaData;
	sockaddr_in server;

	int ret = WSAStartup(0x101, &wsaData); // use highest version of winsock avalible

	if (ret != 0) {
		return;
	}

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(this->serverPort); // listen on telnet port 23

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock == INVALID_SOCKET) {
		return;
	}
 
	if (bind(sock, (sockaddr*)&server, sizeof(server)) != 0) {
		return;
	}

	if (listen(sock, 5) != 0) {
		return;
	}

	SOCKET client;

	sockaddr_in from;
	int fromlen = sizeof(from);

	while (true) {
		client = accept(sock, (struct sockaddr*)&from, &fromlen);
		printf("Client connected\n");

		this->handleClient(client);

		// create our recv_cmds thread and parse client socket as a parameter
		//CreateThread(NULL, 0, receive_cmds, (LPVOID)client, 0, &thread);
	}

	closesocket(sock);
	WSACleanup();

}

void NetworkServer::handleClient(SOCKET client) {

	char buffer[1024];
	int receiveCount = 0;
	bool connected = true;

	while (connected) {
		receiveCount = recv(client, buffer, sizeof(buffer), 0); // recv cmds
		
		if (receiveCount > 0) {
			printf("Receive: %s\n", buffer);
		}
		else {
			connected = false;
			printf("Client disconnected.\n");
		}
	}
}

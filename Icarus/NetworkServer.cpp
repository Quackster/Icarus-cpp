#include <string>
#include <iostream>

#include "stdafx.h"
#include "NetworkServer.h"

using namespace std;

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

		//this->handleClient(client);

		// create our recv_cmds thread and parse client socket as a parameter
		//CreateThread(NULL, 0, handleClient, (LPVOID)client, 0, &thread);

		DWORD myThreadID;
		HANDLE myHandle = CreateThread(0, 0, NetworkServer::handleClient, &client, 0, &myThreadID);

		//sstd::thread connection(&NetworkServer::handleClient, this, client);
	}

	closesocket(sock);
	WSACleanup();

}

DWORD WINAPI NetworkServer::handleClient(LPVOID lpParameter)
{
	SOCKET& client = *((SOCKET*)lpParameter);

	char buffer[1024];

	int receiveCount = 0;
	bool connected = true;

	while (connected) {
		receiveCount = recv(client, buffer, sizeof(buffer), 0); // recv cmds
		
		if (receiveCount > 0) {
			printf("Receive: %i\n", buffer[0]);

			if (buffer[0] == 60) {

				char* policy = "<?xml version=\"1.0\"?>\r\n<!DOCTYPE cross-domain-policy SYSTEM \"/xml/dtds/cross-domain-policy.dtd\">\r\n<cross-domain-policy>\r\n<allow-access-from domain=\"*\" to-ports=\"*\" />\r\n</cross-domain-policy>\0";
				printf("Sent policy: %s", policy);
				send(client, policy, strlen(policy), 0);
			}

		}
		else {
			connected = false;
			printf("Client disconnected.\n");
		}
	}

	return 0;
}

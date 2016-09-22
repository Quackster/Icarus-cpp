#include "stdafx.h"
#include "NetworkConnection.h"

DWORD WINAPI receive_data(LPVOID lpParameter);

NetworkConnection::NetworkConnection(int connectionID, SOCKET socket) : connectionID(connectionID), socket(socket) {
	printf("Client connected with ID: %i\n", this->connectionID);

	DWORD thread; {
		CreateThread(NULL, 0, receive_data, (LPVOID)this, 0, &thread);
	}
}

NetworkConnection::~NetworkConnection() {
}

DWORD WINAPI receive_data(LPVOID lpParameter) {

	NetworkConnection& connection = *((NetworkConnection*)lpParameter);
	SOCKET socket = connection.getSocket();

	char buffer[1024];

	int receiveCount = 0;
	bool connected = true;

	while (connected) {
		receiveCount = recv(socket, buffer, sizeof(buffer), 0); // recv cmds

		if (receiveCount > 0) {
			printf("Receive: (%i) %s\n", strlen(buffer), buffer);

			if (buffer[0] == 60) {

				char* policy = "<?xml version=\"1.0\"?>\r\n<!DOCTYPE cross-domain-policy SYSTEM \"/xml/dtds/cross-domain-policy.dtd\">\r\n<cross-domain-policy>\r\n<allow-access-from domain=\"*\" to-ports=\"*\" />\r\n</cross-domain-policy>\0";
				printf("Sent policy: %s", policy);
				send(connection.getSocket(), policy, strlen(policy) + 1, 0);
			}
			else {


			}

		}
		else {
			connected = false;
			printf("Client disconnected.\n");
		}
	}

	return 0;

}

void NetworkConnection::write_data() {

}

void NetworkConnection::disconnected() {

}

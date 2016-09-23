#include <iostream>

#include "stdafx.h"
#include "NetworkConnection.h"

unsigned long /*DWORD*/ WINAPI receive_data(LPVOID lpParameter);

NetworkConnection::NetworkConnection(int connectionID, SOCKET socket) : connectionID(connectionID), socket(socket) {
	printf("Client connected with ID: %i\n", this->connectionID);
	CreateThread(NULL, 0, receive_data, (LPVOID)this, 0, &thread);
}

NetworkConnection::~NetworkConnection() {


	CloseHandle(&thread);
}

unsigned long WINAPI receive_data(LPVOID lpParameter) {

	NetworkConnection& connection = *((NetworkConnection*)lpParameter);
	SOCKET socket = connection.getSocket();

	char buffer[1024];

	int receiveCount = 0;
	bool connected = true;

	while (connected) {
		receiveCount = recv(socket, buffer, sizeof(buffer), 0); // recv cmds

		if (receiveCount > 6) {
			//printf("Receive: (%i) %s\n", strlen(buffer), buffer);

			if (buffer[0] == 60) {

				char* policy = "<?xml version=\"1.0\"?>\r\n<!DOCTYPE cross-domain-policy SYSTEM \"/xml/dtds/cross-domain-policy.dtd\">\r\n<cross-domain-policy>\r\n<allow-access-from domain=\"*\" to-ports=\"*\" />\r\n</cross-domain-policy>\0";
				printf("Sent policy: %s", policy);
				send(connection.getSocket(), policy, strlen(policy) + 1, 0);
			}
			else {
				int length = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
				short header = ((unsigned char)buffer[5]) | (((unsigned char)buffer[4]) << 8);

				printf("received header: %i\n", header);
			}

			strcpy_s(buffer, "");
			
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

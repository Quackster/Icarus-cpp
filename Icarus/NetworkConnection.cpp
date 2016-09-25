#include "stdafx.h"

#include "Icarus.h"
#include "NetworkConnection.h"
#include "Session.h"

#include "Request.h"

unsigned long /*DWORD*/ WINAPI receive_data(LPVOID lpParameter);

/**
Constructor for NetworkConnection, takes Windows socket instance and connection ID

@param connection ID counter, this is the same ID used to fetch the session from session manager
@param windows socket
@return none
*/
NetworkConnection::NetworkConnection(int connectionID, SOCKET socket) : connectionID(connectionID), socket(socket) {
	printf("Client connected with ID: %i\n", this->connectionID);
	this->createThread();
}

/**
Creates thread for handling packets

@return none
*/
void NetworkConnection::createThread() {
	CreateThread(NULL, 0, receive_data, (LPVOID)this, 0, &thread_id);
}

/**
Windows.h thread handler for recieving packets

@param the parameter (cast to NetworkConnection) given when creating thre thread
*/
unsigned long WINAPI receive_data(LPVOID lpParameter) {

	NetworkConnection& connection = *((NetworkConnection*)lpParameter);
	SOCKET socket = connection.getSocket();

	char buffer[1024];

	int receiveCount = 0;

	while (connection.getConnectionState()) {
		receiveCount = recv(socket, buffer, sizeof(buffer), 0);

		if (receiveCount >= 6) {
			connection.handle_data(buffer, receiveCount);
		} else {

			// Handle session disconnect
			if (Icarus::getSessionManager()->containsSession(connection.getConnectionId())) {
				Icarus::getSessionManager()->getSession(connection.getConnectionId())->disconnected();
			} else {
				// Remove connection if it was just a policy request
				Icarus::getNetworkServer()->removeNetworkConnection(&connection);
			}

			// Stop more code from executing
			return 0;
		}
	}

	return 0;

}

/**
Handle incoming data from the client

@param buffer array
@param the size of the recieved data
@return none
*/
void NetworkConnection::handle_data(char* buffer, int length) {

	if (buffer[0] == 60) {
		this->sendPolicy();
	}
	else {

		// Once we passed through the policy, create a session and handle it
		if (Icarus::getSessionManager()->containsSession(connectionID) == FALSE) {
			Session *session = new Session(this);
			Icarus::getSessionManager()->addSession(session, this->getConnectionId());
		}

		int length = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
		short header = ((unsigned char)buffer[5]) | (((unsigned char)buffer[4]) << 8);

		Request request = Request(header, buffer);

		printf("Received header: %i\n", header);

	}
}

/*
Send policy to the socket

@return none
*/
void NetworkConnection::sendPolicy() {
	char* policy = "<?xml version=\"1.0\"?>\r\n<!DOCTYPE cross-domain-policy SYSTEM \"/xml/dtds/cross-domain-policy.dtd\">\r\n<cross-domain-policy>\r\n<allow-access-from domain=\"*\" to-ports=\"*\" />\r\n</cross-domain-policy>\0";
	send(this->getSocket(), policy, strlen(policy) + 1, 0);
}

void NetworkConnection::write_data(/*char* buffer*/) {

}
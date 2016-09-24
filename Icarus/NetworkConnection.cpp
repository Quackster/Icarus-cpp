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

		if (receiveCount >= 6) {
			connection.handle_data(buffer, receiveCount);
		} else {
			connection.disconnected();
		}
	}

	return 0;

}

void NetworkConnection::handle_data(char* buffer, int length) {

	if (buffer[0] == 60) {

		char* policy = "<?xml version=\"1.0\"?>\r\n<!DOCTYPE cross-domain-policy SYSTEM \"/xml/dtds/cross-domain-policy.dtd\">\r\n<cross-domain-policy>\r\n<allow-access-from domain=\"*\" to-ports=\"*\" />\r\n</cross-domain-policy>\0";
		send(this->getSocket(), policy, strlen(policy) + 1, 0);
	}
	else {

		int length = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
		short header = ((unsigned char)buffer[5]) | (((unsigned char)buffer[4]) << 8);

		if (length > 6) {


			vector<char> message;
			std::stringstream stream;

			for (int i = 0; i < length; i++) {
				message.push_back(buffer[i]);
				stream << buffer[i];
			}

			cout << "packet: " << stream.str() << "\n";


			/*cout << "Received packet: " << header << " / ";

			for (int i = 0; i < length; i++) {

				int char_id = message[i];

				if (char_id >= 0 && char_id <= 13) {
					cout << "[" << char_id << "]";
				}
				else {
					cout << message[i];
				}
			}

			cout << endl;*/
		}
	}

}

void NetworkConnection::write_data() {

}

void NetworkConnection::disconnected() {

}

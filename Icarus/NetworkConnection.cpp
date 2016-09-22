#include "stdafx.h"
#include "NetworkConnection.h"


NetworkConnection::NetworkConnection(int connectionID) : connectionID(connectionID) {
	printf("Client connected with ID: %i\n", this->connectionID);
}

NetworkConnection::~NetworkConnection() {
}

void NetworkConnection::recieve_data() {

}

void NetworkConnection::write_data() {

}

void NetworkConnection::disconnected() {

}

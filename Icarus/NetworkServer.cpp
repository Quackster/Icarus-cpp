#include <string>
#include <iostream>

#include "stdafx.h"
#include "NetworkServer.h"
#include "Session.h"
#include "Icarus.h"

using namespace std;

/*
	@source: http://www.rohitab.com/discuss/topic/26991-cc-how-to-code-a-multi-client-server-in-c-using-threads/
*/

NetworkServer::NetworkServer(short serverPort) 
	: serverPort(serverPort){

	this->connectionID = 0;

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

		NetworkConnection *connection = new NetworkConnection(connectionID++, client);
		Session *session = new Session(connection);

		Icarus::getSessionManager().addSession(session, connection->getConnectionId());
	}

	closesocket(sock);
	WSACleanup();

}

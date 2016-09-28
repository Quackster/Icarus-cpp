#include <string>
#include <iostream>

#include "stdafx.h"
#include "Session.h"
#include "Icarus.h"

using namespace std;

/**
Constructor for NetworkServer

@param server port for listening
@return none
*/
NetworkServer::NetworkServer()  {
    this->connectionID = 0;
}

NetworkServer::~NetworkServer() {
}

/**
Create server for listening on packets, TCP protocol
Source:  http://www.rohitab.com/discuss/topic/26991-cc-how-to-code-a-multi-client-server-in-c-using-threads/

@return none
*/
void NetworkServer::startServer(int serverPort) {

    SOCKET sock;
    WSADATA wsaData;
    sockaddr_in server;

    int ret = WSAStartup(0x101, &wsaData); // use highest version of winsock avalible

    if (ret != 0) {
        return;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(serverPort); 

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
    }

    closesocket(sock);
    WSACleanup();

}

/**
Stops network connection from listening for more packets and deletes it from memory

@param NetworkConnection pointer to delete
@return none
*/
void NetworkServer::removeNetworkConnection(NetworkConnection *connection) {

    // Tell connnection to stop looping for more incoming packets
    connection->setConnectionState(false);

    // Clear connection from memory
    delete connection;
}

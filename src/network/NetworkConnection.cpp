#include "stdafx.h"
#include "Icarus.h"
#include "NetworkConnection.h"
#include "Session.h"
#include "Request.h"

/*DWORD WINAPI*/
unsigned long __stdcall  receive_data(LPVOID lpParameter);

/**
Constructor for NetworkConnection, takes Windows socket instance and connection ID

@param connection ID counter, this is the same ID used to fetch the session from session manager
@param windows socket
@return none
*/
NetworkConnection::NetworkConnection(int connectionID, SOCKET socket) : connectionID(connectionID), socket(socket) {
    this->createThread();
}

NetworkConnection::~NetworkConnection() { }

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
@return thread long
*/
unsigned long __stdcall receive_data(LPVOID lpParameter) {

    NetworkConnection& connection = *((NetworkConnection*)lpParameter);
    SOCKET socket = connection.getSocket();

    char buffer[1024];
    int receiveCount = 0;

    while (connection.getConnectionState()) {

        receiveCount = recv(socket, buffer, sizeof(buffer), 0);

        if (receiveCount >= 6) {
            connection.handle_data(buffer, receiveCount);
        } 
        else {

            // Handle session disconnect
            if (Icarus::getSessionManager()->containsSession(connection.getConnectionId())) {
                Icarus::getSessionManager()->removeSession(connection.getConnectionId());
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

/*
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
        if (!Icarus::getSessionManager()->containsSession(connectionID)) {
            Session *session = new Session(this);
            Icarus::getSessionManager()->addSession(session, this->getConnectionId());
        }

        Request request = Request(buffer);
        cout << " [SESSION] [MESSAGE] Received header: " << request.getMessageId() << endl;

        if (request.getMessageId() == 1490) {

            string authenticationTicket = request.readString();
            cout << "<request> [LOGIN] Received SSO ticket: " << authenticationTicket << endl;

            Response response(1552);
            this->write_data(response);

            response = Response(1351);
            response.writeString("");
            response.writeString("");
            this->write_data(response);

            response = Response(704);
            response.writeInt(0);
            response.writeInt(0);
            this->write_data(response);

        }
    }
}

/*
Handle Response data to send to client

@param response class with data appended to it
@return void
*/
void NetworkConnection::write_data(Response response) {
    try {
        this->sendRaw(response.getData(), response.getBytesWritten());
    } 
    catch (std::exception &e) {
        cout << " Caught exception: " << e.what() << endl;
    }
}

/*
Send policy to the socket

@return void

*/
void NetworkConnection::sendPolicy() {
    char* policy = "<?xml version=\"1.0\"?>\r\n<!DOCTYPE cross-domain-policy SYSTEM \"/xml/dtds/cross-domain-policy.dtd\">\r\n<cross-domain-policy>\r\n<allow-access-from domain=\"*\" to-ports=\"*\" />\r\n</cross-domain-policy>\0";
    this->sendRaw(policy, (int)strlen(policy) + 1);
}

/*
Send raw bytes to socket

@param byte buffer to send
@param the length of byte buffer
@return total number of bytes sent (which can be fewer than the number requested to be sent), or SOCKET_ERROR id is returned
        according to: https://msdn.microsoft.com/en-us/library/windows/desktop/ms740149(v=vs.85).aspx
*/
void NetworkConnection::sendRaw(char* buffer, int len) {
    int socketCode = send(this->socket, buffer, len, 0);

    if (socketCode > 0) {
        if (socketCode < len) {
            cout << " Failure, amount of bytes sent did not reach expected length: << " << socketCode << " bytes sent" << endl;
        }
    }
}

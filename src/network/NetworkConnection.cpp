#include "stdafx.h"

#include "Icarus.h"
#include "NetworkConnection.h"
#include "Session.h"

#include "Request.h"
#include "Response.h"

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

NetworkConnection::~NetworkConnection() {
    //delete this->buffer;
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
        printf(" [SESSION] [MESSAGE] Received header: %i\n", request.getMessageId());
    }
}

/*
    Writes response back to client, will clear buffer at the end

    @param Response class to send
    @return void
*/
void NetworkConnection::write_data(Response response) {

    // Get data to free from memory
    char* data = response.getData();

    // Send data to socket
    send(this->socket, data, response.getBytesWritten(), 0);
    
    // Delete data
    delete[] data;
}

/*
Send policy to the socket

@return none
*/
void NetworkConnection::sendPolicy() {

    char* policy = "<?xml version=\"1.0\"?>\r\n<!DOCTYPE cross-domain-policy SYSTEM \"/xml/dtds/cross-domain-policy.dtd\">\r\n<cross-domain-policy>\r\n<allow-access-from domain=\"*\" to-ports=\"*\" />\r\n</cross-domain-policy>\0";
    send(this->getSocket(), policy, (int)strlen(policy) + 1, 0);
}
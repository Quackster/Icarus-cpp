#include "stdafx.h"

#include "Icarus.h"
#include "NetworkConnection.h"

/*
NetworkConnection constructor

@param connection id
@param tcp::socket connection socket

@return instance
*/
NetworkConnection::NetworkConnection(int connectionID, tcp::socket socket) : connectionID(connectionID), socket_(std::move(socket)) {
    this->connectionState = true;
}

NetworkConnection::~NetworkConnection() { }

/*
Receive data handle

@return none
*/
void NetworkConnection::recieve_data() {

	auto self(shared_from_this());

	socket_.async_read_some(boost::asio::buffer(buffer, sizeof(buffer)), [this, self]( boost::system::error_code ec, std::size_t length) {

        if (!ec) {
            this->handle_data();
            this->recieve_data();
        }
        else {
            
            // Handle session disconnect
            if (Icarus::getSessionManager()->containsSession(this->connectionID)) {
                Icarus::getSessionManager()->removeSession(this->connectionID);
            }
            else {
                // Remove connection if it was just a policy request
                Icarus::getNetworkServer()->removeNetworkConnection(this);
            }
		}

	});
}

/*
Handle incoming data

@return none
*/
void NetworkConnection::handle_data() {

    if (buffer[0] == 60) {
        this->sendPolicy();
    }
    else {

        // Once we passed through the policy, create a session and handle it
        if (!Icarus::getSessionManager()->containsSession(connectionID)) {
            Session *session = new Session(this);
            Icarus::getSessionManager()->addSession(session, this->getConnectionId());
        }

        Request request(buffer);

        cout << "header: " << request.getMessageId() << endl;

        if (request.getMessageId() == 1490) {

            Response response(1552);
            this->send(response);

            response = Response(1351);
            response.writeString("");
            response.writeString("");
            this->send(response);

            response = Response(704);
            response.writeInt(0);
            response.writeInt(0);
            this->send(response);
        }
    }

}


/*
Write data handle

@return none
*/
void NetworkConnection::write_data(char* data, int length) {

	auto self(shared_from_this());
	
	boost::asio::async_write(socket_,boost::asio::buffer(data, /*this->max_length*/length), [this, self, data](boost::system::error_code ec, std::size_t length) {
		if ( !ec ) {
            // send success
		}
	});
}

/*
Send response class to socket

@return none
*/
void NetworkConnection::send(Response response) {
    this->write_data(response.getData(), response.getBytesWritten());
}


/*
Send policy to the socket

@return void

*/
void NetworkConnection::sendPolicy() {
    char* policy = "<?xml version=\"1.0\"?>\r\n<!DOCTYPE cross-domain-policy SYSTEM \"/xml/dtds/cross-domain-policy.dtd\">\r\n<cross-domain-policy>\r\n<allow-access-from domain=\"*\" to-ports=\"*\" />\r\n</cross-domain-policy>\0";
    this->write_data(policy, (int)strlen(policy) + 1);
}

/*
Disconnect handle

@return none
*/
void NetworkConnection::disconnected() {


}

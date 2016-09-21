#include "NetworkConnection.h"

using boost::asio::ip::tcp;


class Session
{
public:
	Session(std::shared_ptr<NetworkConnection> session_connection);
	~Session();
	void disconnected();

private:
	std::shared_ptr<NetworkConnection> networkConnection;

public:
	std::shared_ptr<NetworkConnection> getNetworkConnection() {
		return networkConnection;
	}
};
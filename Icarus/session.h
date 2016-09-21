#include "SessionConnection.h"

using boost::asio::ip::tcp;


class Session
{
public:
	Session(std::shared_ptr<SessionConnection> session_connection);
	~Session();
	void disconnected();

private:
	std::shared_ptr<SessionConnection> session_connection;

public:
	std::shared_ptr<SessionConnection> getNetworkConnection() {
		return session_connection;
	}
};
#include "sessionConnection.h"

using boost::asio::ip::tcp;


class session
{
public:
	session(sessionConnection* session_connection);
	~session();
	void disconnected();

private:
	sessionConnection* session_connection;
};
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class SessionConnection : public std::enable_shared_from_this<SessionConnection>
{
	public:
		SessionConnection(tcp::socket socket);
		~SessionConnection();
		void recieve_data();
		void write_data();
		void disconnected();

	private:
		tcp::socket socket_;
		enum { max_length = 1024 };
		char data_read[max_length];
		char data_write[max_length];
};

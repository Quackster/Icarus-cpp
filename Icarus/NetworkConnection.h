#pragma once
#pragma once

class NetworkConnection {

	public:
		NetworkConnection(int connectionID);
		~NetworkConnection();
		void recieve_data();
		void write_data();
		void disconnected();

	private:
		int connectionID;
		enum { max_length = 1024 };
		char data_read[max_length];
		char data_write[max_length];
};

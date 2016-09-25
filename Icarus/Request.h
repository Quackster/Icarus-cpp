#pragma once
class Request {
public:
	Request(int header, char* full_message);
	~Request();
	int readInt();
	int readString();
	int readShort();
private:
	int header;
	int index;
	char* full_message;
	char* message_body;
};
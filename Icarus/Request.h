#pragma once


class Request {
public:
	Request(char *full_message);
	~Request();

	int readShort();
	int readInt();
	char *readString();

	int getMessageLength() { return length; }
	int getMessageId() { return header;  }

private:
	int header;
	int length;

	int index;
	char *full_message;
};
#pragma once
#include <deque>
#include <iostream>

using namespace std;

class Response
{
public:
	Response(short header);
	~Response();
	char* writeInt(int number);
	char* writeShort(short numberr);
	char* getData();
	char* toBytes();
	char* getBytes(short num);
	char* getBytes(int num, bool reverse = false);
	int getBytesWritten() { return bytes_written;  }
	deque<char> getMessage() { return message; }

private:
	short header;
	int bytes_written;
	bool used;
	deque <char> message;
};


#pragma once
#include <vector>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Response
{
public:
	Response(short header);
	~Response();
	char* writeInt(int number);
	char* writeShort(short number);
	char* getData();

	char* getBytes(short num);
	char* getBytes(int num);

	int getBytesWritten() { return bytes_written;  }
private:
	short header;
	int bytes_written;
	vector<char> message;
};


#include "stdafx.h"
#include "Response.h"

#include <Windows.h>
#include <algorithm>
#include <iterator>

Response::Response(short header) : header(header) {
	this->bytes_written = 0;
	this->message = vector<char>();
	this->writeShort(header);

}

Response::~Response() { }

char* Response::getBytes(short number) {

	char* bytes = static_cast<char*>(static_cast<void*>(&number));
	return bytes;
}

char* Response::getBytes(int number) {

	char* bytes = static_cast<char*>(static_cast<void*>(&number));
	return bytes;
}

char* Response::writeInt(int number) {

	char* bytes = this->getBytes(number);

	for (int i = 0; i < 4; i++) {
		this->message.push_back(bytes[i]);
	}

	this->bytes_written = this->bytes_written + 4;

	return bytes;

}

char* Response::writeShort(short number) {

	char* bytes = this->getBytes(number);

	for (int i = 0; i < 2; i++) {
		this->message.push_back(bytes[i]);
	}

	this->bytes_written = this->bytes_written + 2;

	return bytes;
}

char* Response::getData() {
	
	int length = (int)this->message.size();

	char* output = new char[length + 4];
	char* bytes = this->getBytes(length);

	return output;
}

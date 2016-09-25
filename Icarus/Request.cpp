#include "stdafx.h"
#include "Request.h"

#include <string>
#include <iostream>

Request::Request(char *full_message) : full_message(full_message) {
	this->index = -1;
	this->length = this->readInt();
	this->header = this->readShort();
}

Request::~Request() { }

int Request::readShort() {
	short number = ((unsigned char)this->full_message[this->index+2]) | (((unsigned char)this->full_message[this->index+1]) << 8);
	index = index + 2;
	return number;
}
int Request::readInt() {

	int number = (this->full_message[this->index++] << 24)
		| (this->full_message[this->index++] << 16)
		| (this->full_message[this->index++] << 8)
		| (this->full_message[this->index++]);

	return number;

}

char *Request::readString() {

	int length = readShort();
	char* str = new char[length];

	for (int i = 0; i < length; i++) {
		str[i] = this->full_message[index++];
	}

	return str;
}


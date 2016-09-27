#include "stdafx.h"
#include "Response.h"

/*
Response constructor, it will initialise the deque, and append the header in raw bytes

@parameter header as short
@return response instance
*/
Response::Response(short header) : header(header) {
	this->bytes_written = 0;
	this->used = false;
	this->message = deque <char>(0);
	this->writeShort(header);

}

Response::~Response() { }


/*
Converts a short (16 bits) to little-endian represented in a char array

@parameter reverse, if true, will return in big endian format
@return char array
*/
char* Response::getBytes(short i) {

	char* output = new char[2] {
		(char)(i >> 8),
		(char)i
	};

	return output;
}

/*
Converts a integer (32 bits) to little-endian represented in a char array

@parameter reverse, if true, will return in big endian format
@return char array
*/
char* Response::getBytes(int i, bool reverse) {

	if (reverse) {
		return new char[4]{
		(char)i,
		(char)(i >> 8),
		(char)(i >> 16),
		(char)(i >> 24) };

	} else {
		return new char[4]{
		(char)(i >> 24),
		(char)(i >> 16),
		(char)(i >> 8),
		(char)i };
	};
}

/*
Writes a given integer to 4 bytes in little-endian to the deque

@return char array
*/
char* Response::writeInt(int number) {

	char* bytes = this->getBytes(number);

	for (int i = 0; i < 4; i++) {
		this->message.push_back(bytes[i]);
	}

	this->bytes_written = this->bytes_written + 4;
	return bytes;
}

/*
Gets the entire collection of chars from deque into a single char array

@return none
*/
char* Response::writeShort(short number) {

	char* bytes = this->getBytes(number);
	
	for (int i = 0; i < 2; i++) {
		this->message.push_back(bytes[i]);
	}

	this->bytes_written = this->bytes_written + 2;
	return bytes;
}

/*
Gets the entire collection of chars from deque into a single char array
with 32 bit length prefixed

@return char array of packet
*/
char* Response::getData() {
	
	if (!this->used) {
		char* size_raw = this->getBytes(this->bytes_written, true);
		this->bytes_written = this->bytes_written + 4; // increase bytes written

		for (int i = 0; i < 4; i++) {
			this->message.push_front(size_raw[i]);
		}

		this->used = true;
	}
		
	return toBytes();
}

/*
Gets the entire collection of chars from deque into a single char array

@return char array of collection
*/
char* Response::toBytes() {

	int size = this->message.size();
	char* output = new char[size];

	for (int i = 0; i < size; i++) {
		output[i] = this->message[i];
	}

	return output;
}

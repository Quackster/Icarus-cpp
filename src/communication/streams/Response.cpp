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

    char bytes[2];
    
    bytes[0] = (char)(i >> 8);
    bytes[1] = (char)i;

    return bytes;
}

/*
Converts a integer (32 bits) to little-endian represented in a char array

@parameter reverse, if true, will return in big endian format
@return char array
*/
char* Response::getBytes(int i, bool reverse) {

    char bytes[4];

    if (reverse) {
        bytes[0] = (char)i;
        bytes[1] = (char)(i >> 8);
        bytes[2] = (char)(i >> 16);
        bytes[3] = (char)(i >> 24);

    } else {
        bytes[3] = (char)i;
        bytes[2] = (char)(i >> 8);
        bytes[1] = (char)(i >> 16);
        bytes[0] = (char)(i >> 24);
    };

    return bytes;
}

/*
Writes a given integer in 4 bytes in little-endian format to the deque
and increases the bytes written by 4

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
Writes a given short in 2 bytes in little-endian format to the deque
and increases the bytes written by 2

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
Writes a given string with length prefixed in UTF-8 format
and increases the bytes written by 2

@return none
*/
void Response::writeString(char* str) {

    short length = strlen(str);
    this->writeShort(length);

    for (int i = 0; i < length; i++) {
        this->message.push_back(str[i]);
    }

    this->bytes_written = this->bytes_written + length;
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

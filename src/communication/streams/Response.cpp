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
    this->message = vector <char>(0);
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
Writes a given integer in 4 bytes in little-endian format to the deque
and increases the bytes written by 4

@return char array
*/
void Response::writeInt(int number) {

    char* bytes = this->getBytes(number);

    for (int i = 0; i < 4; i++) {
        this->message.push_back(bytes[i]);
    }

    this->bytes_written = this->bytes_written + 4;
    delete[] bytes;
}

/*
Writes a given short in 2 bytes in little-endian format to the deque
and increases the bytes written by 2

@return none
*/
void Response::writeShort(short number) {

    char* bytes = this->getBytes(number);
    
    for (int i = 0; i < 2; i++) {
        this->message.push_back(bytes[i]);
    }

    this->bytes_written = this->bytes_written + 2;
    delete[] bytes;
}

/*
Writes a given string with length prefixed in UTF-8 format
and increases the bytes written by 2

@return none
*/
void Response::writeCChar(const char* str) {

    short length = (short)strlen(str);
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
        this->used = true;

        // Get the size in raw 4 int 32 length prefixed, but reversed
        // as this needs to be inserted at the front
        char* size_raw = this->getBytes(this->bytes_written, true);

        for (int i = 0; i < 4; i++) {

            // Insert at the front of vector
            this->message.insert(this->message.begin(), size_raw[i]);
        }
    }
        
    return this->message.data();
}

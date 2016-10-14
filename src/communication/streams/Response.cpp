/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"
#include "communication/streams/Response.h"

/*
Response constructor, it will initialise the deque, and append the header in raw bytes

@parameter header as short
@return response instance
*/
Response::Response(short header) : 
    header(header), index(0), used(false), message(std::vector<char>(0)) {
    
    this->writeShort(header);
}

Response::~Response() { }

/*
Converts a short (16 bits) to little-endian represented in a char array

@parameter reverse, if true, will return in big endian format
@return char array
*/
char* Response::getBytes(short i) {

    char *output = new char[2];

    output[0] = (char)(i >> 8) & 0xff;
    output[1] = (char)(i) & 0xff;

    return output;
}

/*
Converts a integer (32 bits) to little-endian represented in a char array

@parameter reverse, if true, will return in big endian format
@return char array
*/
char* Response::getBytes(int i, bool reverse) {

    char *output = new char[4];

    if (reverse) {
        output[0] = (char)i & 0xff;
        output[1] = (char)(i >> 8) & 0xff;
        output[2] = (char)(i >> 16) & 0xff;
        output[3] = (char)(i >> 24) & 0xff;
    } else {
        output[3] = (char)i & 0xff;
        output[2] = (char)(i >> 8) & 0xff;
        output[1] = (char)(i >> 16) & 0xff;
        output[0] = (char)(i >> 24) & 0xff;
    };

    return output;
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

    this->index = this->index + 4;
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

    this->index = this->index + 2;
    delete[] bytes;
}

/*
Writes a given string with length prefixed in UTF-8 format
and increases the bytes written by 2, and including the length of the string

@return none
*/
void Response::writeCChar(const char* str) {

    short length = (short)strlen(str);
    this->writeShort(length);

    for (int i = 0; i < length; i++) {
        this->message.push_back(str[i]);
    }

    this->index = this->index + length;
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
        char* size = this->getBytes(this->index, true);

        for (int i = 0; i < 4; i++) {

            // Insert at the front of vector
            this->message.insert(this->message.begin(), size[i]);
        }

        delete[] size;
    }
        
    return this->message.data();
}

/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"
#include "Response.h"

/*
Response constructor, it will initialise the deque, and append the header in raw bytes

@parameter header as short
@return response instance
*/
Response::Response(short header) : 
    header(header), 
    index(0), 
    used(false), 
    message(std::vector<char>(0)) {

    this->writeShort(header);
}

Response::~Response() { }


/*
Writes a given integer in 4 bytes in little-endian format to the deque
and increases the bytes written by 4

@return char array
*/
void Response::writeInt(int value) {

    char output[4];

	output[0] = (char)(value >> 24);
	output[1] = (char)(value >> 16);
	output[2] = (char)(value >> 8);
	output[3] = (char)(value);

    for (int i = 0; i < 4; i++) {
        this->message.push_back(output[i]);
    }

    this->index = this->index + 4;
}

/*
Writes a given short in 2 bytes in little-endian format to the deque
and increases the bytes written by 2

@return none
*/
void Response::writeShort(short number) {

    char output[2];

    output[0] = (char)(number >> 8) & 0xff;
    output[1] = (char)number & 0xff;

    for (int i = 0; i < 2; i++) {
        this->message.push_back(output[i]);
    }

    this->index = this->index + 2;
    //delete[] bytes;
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
        //char* size = this->getBytes(this->index, true);

        char size[4];

        size[0] = (char)this->index & 0xff;
        size[1] = (char)(this->index >> 8) & 0xff;
        size[2] = (char)(this->index >> 16) & 0xff;
        size[3] = (char)(this->index >> 24) & 0xff;

        for (int i = 0; i < 4; i++) {
            this->message.insert(this->message.begin(), size[i]);
        }
    }
        
    return this->message.data();
}
#include "stdafx.h"
#include "Request.h"

#include <string>
#include <iostream>

/*
Request constructor

@return full received packet
*/
Request::Request(char *full_message) : full_message(full_message) {
    this->index = 0;

    this->length = this->readInt();
    this->header = this->readShort();
}

Request::~Request() { }

/*
Read an integer represented as 16 bits

@return integer
*/
int Request::readShort() {
    short number = ((unsigned char)this->full_message[this->index + 1]) | (((unsigned char)this->full_message[this->index]) << 8);
    index = index + 2;
    return number;
}

/*
Read an integer represented as 32 bits

@return integer
*/
int Request::readInt() {

    int number = (this->full_message[this->index] << 24)
        | (this->full_message[this->index + 1] << 16)
        | (this->full_message[this->index + 2] << 8)
        | (this->full_message[this->index + 3]);

    index = index + 4;
    return number;

}

/*
Read a string with a 16bit length prefixed

@return string
*/
char *Request::readString() {

    int length = readShort();
    char* str = new char[length];
    
    for (int i = 0; i < length; i++) {
        str[i] = this->full_message[index++];
    }

    str[length] = '\0'; // Null terminate, needed for C++
    return str;
}


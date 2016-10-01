#include "stdafx.h"
#include "Request.h"

/*
Request constructor

@return full received packet
*/
Request::Request(char *full_message) : full_message(full_message) {
    this->index = 0;

    //this->length = this->readInt();
    this->header = this->readShort();
}

Request::~Request() { }

/*
Read an integer represented as 16 bits

@return integer
*/
int Request::readShort() {

    short number = (short)(
        (0xff & full_message[index]) << 8 |
        (0xff & full_message[index + 1]) << 0);

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
std::string Request::readString() {

    int length = readShort();
    std::string str;
    

    for (int i = 0; i < length; i++) {
        str += this->full_message[index++];
    }

    return str;
}


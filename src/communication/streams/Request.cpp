#include "stdafx.h"
#include "communication/streams/Request.h"

/*
Request constructor

@return full received packet
*/
Request::Request(char *fullMessage) : fullMessage(fullMessage) {
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
        (0xff & fullMessage[index]) << 8 |
        (0xff & fullMessage[index + 1]) << 0);

    index = index + 2;
    return number;
}

/*
Read an integer represented as 32 bits

@return integer
*/
int Request::readInt() {

    int number = (this->fullMessage[this->index] << 24)
        | (this->fullMessage[this->index + 1] << 16)
        | (this->fullMessage[this->index + 2] << 8)
        | (this->fullMessage[this->index + 3]);

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
        str += this->fullMessage[index++];
    }

    return str;
}


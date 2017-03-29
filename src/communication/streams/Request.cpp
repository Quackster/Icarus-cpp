/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"
#include "Request.h"

#include "misc/encoding/Base64Encoding.h"
#include "misc/encoding/WiredEncoding.h"

/*
Request constructor

@return full received packet
*/
Request::Request(int length, char *full_message) : 
    length(length),
    bytes(full_message), 
    offset(0) {

    if (length > 0) {
        this->header = this->readB64();
    }
}

Request::~Request() { }

/*
Read an boolean represented as 1 byte

@return boolean
*/
bool Request::readBool() {

    char number = ((int)bytes[offset]) == 1;

    offset = offset + 1;
    return number;
}

/*
Read an integer represented as 16 bits

@return integer
*/
int Request::readB64() {

    short number = Base64Encoding::decodeB64(std::string({ bytes[offset], bytes[offset + 1] }));

    offset = offset + 2;
    return number;
}


/*
Read an integer represented as 32 bits

@return integer
*/
long Request::readInt() {

    int length = 0;
    long result = WiredEncoding::decode(readBytesFreezeCursor(6).data(), length);

    offset = offset + length;
    return result;

}

/*
Read a string with a 16bit length prefixed

@return string
*/
std::string Request::readString() {
    std::string str;

    int length = this->readB64();

    for (int i = 0; i < length; i++) {
        str += this->bytes[offset++];
    }


    return str;
}

std::vector<char> Request::readBytesFreezeCursor(int num_bytes) {

    if (num_bytes > this->getRemainingData())
        num_bytes = this->getRemainingData();

    std::vector<char> bzData;
    bzData.resize(num_bytes);

    for (int x = 0, y = offset; x < num_bytes; x++, y++) {
        bzData.at(x) = this->bytes[y];
    }

    return bzData;
}

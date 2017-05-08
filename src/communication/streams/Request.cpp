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

/*
Request constructor

@return full received packet
*/
Request::Request(int length, char *full_message) : 
    length(length),
    bytes(full_message), 
    offset(0) {

    if (length > 0) {
        this->header = this->readShort();
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
short Request::readShort() {

    short number = (short)(
        (0xff & bytes[offset]) << 8 |
        (0xff & bytes[offset + 1]) << 0);

    offset = offset + 2;
    return number;
}


/*
Read an integer represented as 32 bits

@return integer
*/
long Request::readInt() {

    long result = (int)bytes[offset + 3] & 0xff;
    result |= ((int)bytes[offset + 2] & 0xff) << 8;
    result |= ((int)bytes[offset + 1] & 0xff) << 16;
    result |= ((int)bytes[offset] & 0xff) << 24;

    offset = offset + 4;
    return result & 0xFFFFFFFFL;

}

/*
Read a string with a 16bit length prefixed

@return string
*/
std::string Request::readString() {
	std::string str;

	int length = readShort();

	for (int i = 0; i < length; i++) {
		str += this->bytes[offset++];
	}

	return str;
}


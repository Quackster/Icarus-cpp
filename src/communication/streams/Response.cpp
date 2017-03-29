/**
* Roseau - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#include "stdafx.h"

#include "Response.h"

#include "misc/encoding/Base64Encoding.h"
#include "misc/encoding/WiredEncoding.h"

Response::Response(int header) {
    this->set(header);
}

Response::~Response() { }

void Response::set(int header) {
    this->header = header;
    this->bytes = std::vector<char>();
    this->used = false;
}
void Response::writeInt(int number) {

    char *encoded = WiredEncoding::encode(number);

    for (int i = 0; i < 2; i++) {
        this->bytes.push_back(encoded[i]);
    }

}
void Response::writeBool(bool state) {

    if (state) {
        this->bytes.push_back(WiredEncoding::POSITIVE);
    }
    else {
        this->bytes.push_back(WiredEncoding::NEGATIVE);
    }
}

void Response::writeString(std::string str) {

    for (int i = 0; i < str.length(); i++) {
        this->bytes.push_back(str.c_str()[i]);
    }

    this->bytes.push_back((char)2);
}

void Response::write(std::string str) {

    for (int i = 0; i < str.length(); i++) {
        this->bytes.push_back(str.c_str()[i]);
    }
}

char *Response::getBytes() {

    if (!used) {
        used = true;
        std::vector<char> output;

        const char *message_header = Base64Encoding::encodeB64(this->header);

        output.push_back(message_header[0]);
        output.push_back(message_header[1]);

        for (int i = 0; i < this->bytes.size(); i++)
        {
            //std::cout << "SENT: " << this->bytes.at(i) << " / " << 3 << endl;
            output.push_back(this->bytes.at(i));
        }

        output.push_back((char)1);

        this->bytes.clear();
        this->bytes = output;
    }

    return bytes.data();
}

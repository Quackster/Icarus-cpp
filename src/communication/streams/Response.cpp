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
    this->message = std::vector<char>();
    this->used = false;
    this->size = 3; // header + chr 1 at the end
}
void Response::writeInt(int number) {

    char *encoded = WiredEncoding::encode(number);

    for (int i = 0; i < 2; i++) {
        this->message.push_back(encoded[i]);
    }

    this->size = this->size + 2;
}
void Response::writeBool(bool state) {

    if (state) {
        this->message.push_back(WiredEncoding::POSITIVE);
    }
    else {
        this->message.push_back(WiredEncoding::NEGATIVE);
    }

    this->size = this->size + 1;
}

void Response::writeString(std::string str) {

    for (int i = 0; i < str.length(); i++) {
        this->message.push_back(str.c_str()[i]);
        this->size = this->size + 1;
    }

    this->message.push_back((char)2);
    this->size = this->size + 1;
}

void Response::write(std::string str) {

    for (int i = 0; i < str.length(); i++) {
        this->message.push_back(str.c_str()[i]);
        this->size = this->size + 1;
    }
}

char *Response::getBytes() {

    if (!used) {
        used = true;
        std::vector<char> output;

        const char *message_header = Base64Encoding::encodeB64(this->header);

        output.push_back(message_header[0]);
        output.push_back(message_header[1]);

        for (int i = 0; i < this->message.size(); i++)
        {
            //std::cout << "SENT: " << this->bytes.at(i) << " / " << 3 << endl;
            output.push_back(this->message.at(i));
        }

        output.push_back((char)1);

        this->bytes = output.data();
    }

    return bytes;
}

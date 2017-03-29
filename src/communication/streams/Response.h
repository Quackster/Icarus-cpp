/**
* Roseau - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <string>
#include <vector>

class Response
{
public:
    Response(int header);
    ~Response();

    void set(int header);
    void writeInt(int number);
    void writeBool(bool state);

    void writeString(int i) {
        this->writeString(std::to_string(i));
    }

    void writeString(std::string str);
    void write(std::string str);

    std::string getContentString();
    std::vector<char> &getBytes();

    int getSize() { return size; }
    int getHeader() { return header; };

private:

    std::vector<char> message;
    char *bytes;
    bool used = false;

    int header;
    int size;
};




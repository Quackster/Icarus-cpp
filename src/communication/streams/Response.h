/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include <memory>
#include <vector>
#include <string>
#include <cstring> // Required for G++/GCC compilation with function "strlen"

class Response
{

public:
    Response() : header(0) {};
    Response(short header);
    ~Response();
    void writeInt(int number);
    void writeInt(bool flag) { this->writeInt(flag ? 1 : 0);  }
    void writeInt(size_t number) { this->writeInt((int)number); }
    void writeBool(bool flag) {
        this->message.push_back(flag ? (char)1 : (char)0);
        this->index = this->index + 1;
    }
    void writeShort(short numberr);
    void writeString(const char* str) { this->writeCChar(str); };
    void writeString(int str) { this->writeString(std::to_string(str)); };
    void writeString(std::string str) { this->writeCChar(str.c_str()); };

    char *getData();
    //char *getBytes(short num);
    //char *getBytes(int num, bool reverse = false);

    int getBytesWritten() { return index + 4/*the length at the start*/;  }
    std::vector<char> getMessage() { return message; }
    int getHeader() { return header; }

private:
    short header;
    int index;
    bool used;
    std::vector <char> message;
    void writeCChar(const char* str);
    enum { MAX_RESPONSE_SIZE = 1024 };
};


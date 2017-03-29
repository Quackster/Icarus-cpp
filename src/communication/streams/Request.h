/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once
#include <vector>

class Request 
{

public:
    Request(int length, char *full_message);
    ~Request();

    int readB64();
    long readInt();
    bool readBool();
    std::string readString();
    std::vector<char> readBytesFreezeCursor(int num_bytes);
    int getRemainingData() { return length - offset; }

    int getMessageLength() { return length; }
    short getMessageId() { return header;  }
    char* getBuffer() { return bytes;  }

private:
    short header;
    
    int length;
    int remaining_data;

    int offset;

    char *bytes;
};
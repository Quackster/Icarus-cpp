/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

#include <iostream>

class Request 
{

public:
    Request(char *full_message);
    ~Request();

    short readShort();
    int readInt();
    bool readBool();
    std::string readString();

    int getMessageLength() { return length; }
    short getMessageId() { return header;  }
    char* getBuffer() { return full_message;  }

private:
    short header;
    int length;
    int index;

    char *full_message;
};
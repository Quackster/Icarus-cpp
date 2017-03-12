/**
* Icarus - A multi-platform C++ server
*
* Copyright 2016 Alex "Quackster" Miller
*
* Licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License
* (see https://creativecommons.org/licenses/by-nc-sa/4.0/, or LICENSE.txt for a full license
*/
#pragma once

class Request 
{

public:
    Request(int length, char *full_message);
    ~Request();

    short readShort();
    long readInt();
    bool readBool();
    std::string readString();

    int getMessageLength() { return length; }
    short getMessageId() { return header;  }
    char* getBuffer() { return bytes;  }

private:
    short header;
    int length;
    int offset;

    char *bytes;
};
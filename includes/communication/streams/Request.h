#pragma once

#include <iostream>

class Request 
{

public:
    Request(char *full_message);
    ~Request();

    short readShort();
    int readInt();
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
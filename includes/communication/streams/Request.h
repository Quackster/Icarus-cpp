#pragma once

#include <iostream>

class Request 
{

public:
    Request(char *full_message);
    ~Request();

    int readShort();
    int readInt();
    std::string readString();

    int getMessageLength() { return length; }
    int getMessageId() { return header;  }
    char* getBuffer() { return full_message;  }

private:
    int header;
    int length;
    int index;

    char *full_message;
};
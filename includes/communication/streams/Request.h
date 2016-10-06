#pragma once

#include <iostream>

class Request 
{

public:
    Request(char *fullMessage);
    ~Request();

    int readShort();
    int readInt();
    std::string readString();

    int getMessageLength() { return length; }
    int getMessageId() { return header;  }

private:
    int header;
    int length;
    int index;

    char *fullMessage;
};
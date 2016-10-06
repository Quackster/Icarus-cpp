#pragma once

#include <string>
#include <iostream>

using namespace std;

class Request 
{

public:
    Request(char *fullMessage);
    ~Request();

    int readShort();
    int readInt();
    string readString();

    int getMessageLength() { return length; }
    int getMessageId() { return header;  }

private:
    int header;
    int length;
    int index;

    char *fullMessage;
};
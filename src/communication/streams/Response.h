#pragma once
#include <deque>
#include <iostream>

using namespace std;

class Response
{

public:
    Response(short header);
    ~Response();
    char* writeInt(int number);
    char* writeShort(short numberr);
    void writeString(char* str);
    char* getData();
    char* toBytes();
    char* getBytes(short num);
    char* getBytes(int num, bool reverse = false);
    int getBytesWritten() { return bytes_written + 4/*the length at the start*/;  }
    deque<char> getMessage() { return message; }
    bool isUsed() { return used;  }

private:
    short header;
    int bytes_written;
    bool used;
    deque <char> message;

    enum { MAX_RESPONSE_SIZE = 1024 };
};


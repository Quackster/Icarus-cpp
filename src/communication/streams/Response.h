#pragma once
#include <deque>
#include <iostream>
#include <string>

using namespace std;

class Response
{

public:
    Response(short header);
    ~Response();
    void writeInt(int number);
    void writeShort(short numberr);
    void writeString(const char* str) { this->writeCChar(str); };
    void writeString(string str) { this->writeCChar(str.c_str()); };
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

    void writeCChar(const char* str);

    enum { MAX_RESPONSE_SIZE = 1024 };
};


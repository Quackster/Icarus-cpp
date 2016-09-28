#pragma once
#include <deque>
#include <iostream>

using namespace std;

class Response
{
public:
    Response(short header);
    ~Response();
    void writeInt(int number);
    void writeShort(short numberr);
    void writeString(string str);
    void writeString(char* str) { writeString(string(str));  };
    char* getData();
    char* toBytes();
    char* getBytes(short num);
    char* getBytes(int num, bool reverse = false);
    int getBytesWritten() { return bytes_written + 4/*the length at the start*/; }
    deque<char> getMessage() { return message; }

private:
    short header;
    int bytes_written;
    bool used;
    deque <char> message;
};

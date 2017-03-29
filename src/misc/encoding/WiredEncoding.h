#pragma once
class WiredEncoding
{
public:
    static const char NEGATIVE = (char)72; // 'H'
    static const char POSITIVE = (char)73; // 'I'

    static char *encode(int i);
    static int decode(char *data, int &total_bytes);
};


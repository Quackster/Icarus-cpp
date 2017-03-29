#pragma once

#include <vector>

class Base64Encoding
{
public:
    static const char* encodeB64(int i);
    static int decodeB64(const std::string str, int len = 2);
};


#include "stdafx.h"

#include <string>

#include "misc/encoding/Base64Encoding.h"

const char* Base64Encoding::encodeB64(int i)
{
    std::vector<char> bzData;
    bzData.resize(2);

    for (int j = 1; j <= 2; j++) {
        
        int k = ((2 - j) * 6);
        bzData.at(j - 1) = (char)(0x40 + ((i >> k) & 0x3f));
    }


    return bzData.data();
}

int Base64Encoding::decodeB64(const std::string str, int len) {

    const char *data = str.c_str();

    int i = 0;
    int j = 0;

    for (int k = str.length() - 1; k >= 0; k--) {
        int x = data[k] - 0x40;
        if (j > 0)
            x *= (int)std::pow(64.0, (double)j);

        i += x;
        j++;
    }

    return i;
}

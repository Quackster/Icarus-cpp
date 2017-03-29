#include "stdafx.h"

#include <vector>

#include "misc/encoding/WiredEncoding.h"

char *WiredEncoding::encode(int i, int &total_bytes)
{
    const int MAX_INTEGER_BYTE_AMOUNT = 6;

    char wf[MAX_INTEGER_BYTE_AMOUNT];
    int pos = 0;
    int numBytes = 1;
    int startPos = pos;
    int negativeMask = i >= 0 ? 0 : 4;
    i = std::abs(i);
    wf[pos++] = (char)(64 + (i & 3));

    for (i >>= 2; i != 0; i >>= MAX_INTEGER_BYTE_AMOUNT)
    {
        numBytes++;
        wf[pos++] = (char)(64 + (i & 0x3f));
    }
    wf[startPos] = (char)(wf[startPos] | numBytes << 3 | negativeMask);

    // Skip the null bytes in the result
    //char bzData[2];// = new byte[numBytes];

    total_bytes = numBytes;

    std::vector<char> bzData;
    bzData.resize(numBytes);

    for (int x = 0; x < numBytes; x++)
    {
        bzData.at(x) = wf[x];
    }

    return bzData.data();
}

int WiredEncoding::decode(char *data, int &total_bytes) {

    int pos = 0;
    int v = 0;
    bool negative = (data[pos] & 4) == 4;
    total_bytes = data[pos] >> 3 & 7;
    v = data[pos] & 3;
    pos++;
    int shiftAmount = 2;
    for (int b = 1; b < total_bytes; b++)
    {
        v |= (data[pos] & 0x3f) << shiftAmount;
        shiftAmount = 2 + 6 * b;
        pos++;
    }

    if (negative == true)
        v *= -1;

    return v;

}

//============================================================================
// Name        : Matasano.cpp
// Author      : Sebastien Boutin
// Version     :
// Copyright   : free
// Description :
//============================================================================

#include <iostream>
#include <string>
#include <cassert>
#include <cstring>

#include "lib.h"
using namespace std;

string base64="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//void hexDecode(const char* input, uint8_t* out )
//{
//    std::string myString(input);
//
//    for (int i=0;i<strlen(input);i+=2) {
//        std::string substr = myString.substr(i,2);
//        out[i] = strtoul(substr.c_str(), 0, 16);
//    }
//}

void hexDecode(const char* input, uint8_t* out )
{
    //uint8_t* out = new uint8_t[strlen(input)/2];

    std::string myString(input);

    for (int i=0;i<(myString.size())/2;i++) {
        std::string subStr = myString.substr(i*2,2);
        out[i] = strtoul(subStr.c_str(), 0, 16);
    }
//    return out;
}

char* base64Encode(const char* input, int size) {
    /** Encode an input made of raw bytes in base64.
     *
     * @param input String input treated as raw bytes.
     * @param size String size.
     *
     * Note on the masks used:
     *
     * 0xFC
     * 0x03
     * 0xF0
     * 0x0F
     * 0xC0
     * 0x3F
     */
    uint8_t a, b, c, d, e, f,g;
    int output_length;
    int padding = size%3;

    // Set the output size
    if (padding == 0) {
        output_length = (size / 3) * 4; // Every 3 letters, 4 letters are created, plus the 4 last ones.
    } else {
        output_length = (size / 3) * 4 + 4; // Every 3 letters, 4 letters are created, plus the 4 last ones.
    }

    output_length += 1; // Terminate the string with the null character.
    char* output = new char[output_length];

    // Treat the 3-tuples.
    int output_position = 0; // track the position in the output array.
    for (int i = 0; i < (size - padding); i+=3)
    {
        a = (input[i] & 0xFC) >> 2;
        b = (input[i] & 0x03) << 4 ^ (input[i + 1] & 0xF0) >> 4;
        c = (input[i + 1] & 0x0F) << 2 ^ (input[i + 2] & 0xC0) >> 6;
        d = (input[i + 2] & 0x3F);

        output[output_position++] = base64[a];
        output[output_position++] = base64[b];
        output[output_position++] = base64[c];
        output[output_position++] = base64[d];
    }

    // Treat the end of the string when 2 characters remain.
    if (padding == 2) {
        e = (input[size - 2] & 0xFC) >> 2;
        f = (input[size - 2] & 0x03) << 4 ^ (input[size - 1] & 0xF0) >> 4;
        g = (input[size - 1] & 0x0F) << 2;

        output[output_position++] = base64[e];
        output[output_position++] = base64[f];
        output[output_position++] = base64[g];
        output[output_position++] = '=';
    }

    // Treat the end when 1 character remain.
    if (padding == 1) {
        e = (input[size - 1] & 0xFC) >> 2;
        f = (input[size - 1] & 0x03) << 4;

        output[output_position++] = base64[e];
        output[output_position++] = base64[f];
        output[output_position++] = '=';
        output[output_position++] = '=';
    }

    output[output_position++] = '\0';
    return output;
}

uint8_t* base64Decode(const char* input, int size)
{
    int padding = 0;
    uint8_t a, b, c, d;
    // Padding ?
    if (input[size-1] == '=') {
        padding=1;
        if (input[size-2] == '=')
            padding=2;
    }

    // Set the output size
    int output_length;
    if (padding == 1)
        output_length = (size / 4) * 3 + 2;
    if (padding == 2)
        output_length = (size / 4) * 3 + 1;


    int output_position = 0; // track the position in the output array.

    uint8_t* output = new uint8_t[output_length];

    for (int i = 0; i < (size - (size-padding)%4); i+=4)
    {
        a = base64.find(input[i]);
        b = base64.find(input[i+1]);
        c = base64.find(input[i+2]);
        d = base64.find(input[i+3]);

        output[output_position++] = a << 2 ^ (b & 0x30) >> 4;
        output[output_position++] = (b & 0x0F) << 4 ^ (c & 0x3C) >> 2;
        output[output_position++] = (c & 0x03) << 6 ^ (d & 0x3F);
    }

    // Treat the end of the string when 2 characters remain.
    if (padding == 2) {
        output[output_position-2] = '\0';
        // a = base64.find(input[size-4]);
        // b = base64.find(input[size-3]);
        // c = base64.find(input[size-2]);

        // output[output_position++] = a << 2 ^ (b & 0x30) >> 4;
        // output[output_position++] = (b & 0x0F) << 4 ^ (c & 0x3C) >> 2;
    }

    // Treat the end when 1 character remain.
    if (padding == 1) {
        output[output_position-1] = '\0';
        // a = base64.find(input[size-4]);
        // b = base64.find(input[size-3]);

        // output[output_position++] = a << 2 ^ (b & 0x30) >> 4;
    }

    output[output_position++] = '\0';

    return output;
}



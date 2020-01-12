//============================================================================
// Name        : Matasano.cpp
// Author      : Sebastien Boutin
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <string>
#include <cassert>
#include <cstring>

using namespace std;

string base64="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


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
    int output_length = (size / 4) * 3 + padding;
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
        a = base64.find(input[size-4]);
        b = base64.find(input[size-3]);
        c = base64.find(input[size-2]);

        output[output_position++] = a << 2 ^ (b & 0x30) >> 4;
        output[output_position++] = (b & 0x0F) << 4 ^ (c & 0x3C) >> 2;
    }

    // Treat the end when 1 character remain.
    if (padding == 1) {
        a = base64.find(input[size-4]);
        b = base64.find(input[size-3]);

        output[output_position++] = a << 2 ^ (b & 0x30) >> 4;
    }


    return output;
}

int getLength(const char* s)
{
    char c = s[0];
    int count = 0;
    while (c != '\0') {
        count++;
        c = s[count];
    }
    return count;
}


int main() {

    // Sources of the inputs:
    // https://en.wikipedia.org/wiki/Base64

    // Declarations like
    char* res1;
    char* res2;
    char* res3;
    char* res4;
    char* res5;
    char* res6;
    char* res7;
    char* res8;
    char* res9;
    char* res10;

    const char* input_1 = "any carnal pleasure.";
    const char* input_2 = "any carnal pleasure";
    const char* input_3 = "any carnal pleasur";
    const char* input_4 = "any carnal pleasu";
    const char* input_5 = "any carnal pleas";
    const char* input_6 = "pleasure.";
    const char* input_7 = "leasure.";
    const char* input_8 = "easure.";
    const char* input_9 = "asure.";
    const char* input_10 = "sure.";

    const char* expected_output_1 = "YW55IGNhcm5hbCBwbGVhc3VyZS4=";
    const char* expected_output_2 = "YW55IGNhcm5hbCBwbGVhc3VyZQ==";
    const char* expected_output_3 = "YW55IGNhcm5hbCBwbGVhc3Vy";
    const char* expected_output_4 = "YW55IGNhcm5hbCBwbGVhc3U=";
    const char* expected_output_5 = "YW55IGNhcm5hbCBwbGVhcw==";
    const char* expected_output_6 = "cGxlYXN1cmUu";
    const char* expected_output_7 = "bGVhc3VyZS4=";
    const char* expected_output_8 = "ZWFzdXJlLg==";
    const char* expected_output_9 = "YXN1cmUu";
    const char* expected_output_10 = "c3VyZS4=";

    const char challenge[] = {0x49,0x27,0x6d,0x20,0x6b,0x69,0x6c,0x6c,0x69,0x6e,0x67,0x20,0x79,0x6f,0x75,0x72,0x20,0x62,0x72,0x61,0x69,0x6e,0x20,0x6c,0x69,0x6b,0x65,0x20,0x61,0x20,0x70,0x6f,0x69,0x73,0x6f,0x6e,0x6f,0x75,0x73,0x20,0x6d,0x75,0x73,0x68,0x72,0x6f,0x6f,0x6d};
    const char* expected = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
    int size_challenge = sizeof(challenge);

    // Tests
    res1 = base64Encode(input_1,getLength(input_1));
    res2 = base64Encode(input_2,getLength(input_2));
    res3 = base64Encode(input_3,getLength(input_3));
    res4 = base64Encode(input_4,getLength(input_4));
    res5 = base64Encode(input_5,getLength(input_5));
    res6 = base64Encode(input_6,getLength(input_6));
    res7 = base64Encode(input_7,getLength(input_7));
    res8 = base64Encode(input_8,getLength(input_8));
    res9 = base64Encode(input_9,getLength(input_9));
    res10 = base64Encode(input_10,getLength(input_10));

    // Encoding tests
    assert(strcmp(res1,expected_output_1) == 0);
    assert(strcmp(res2,expected_output_2) == 0);
    assert(strcmp(res3,expected_output_3) == 0);
    assert(strcmp(res4,expected_output_4) == 0);
    assert(strcmp(res5,expected_output_5) == 0);

    assert(strcmp(res6,expected_output_6) == 0);
    assert(strcmp(res7,expected_output_7) == 0);
    assert(strcmp(res8,expected_output_8) == 0);
    assert(strcmp(res9,expected_output_9) == 0);
    assert(strcmp(res10,expected_output_10) == 0);

    // Decoding tests
    uint8_t* decoded = base64Decode(expected_output_1,strlen(expected_output_1));
    cout << "decoded:" << decoded << endl;

    char* result = base64Encode(challenge,size_challenge);
    assert(strcmp(result,expected) == 0);

    cout << result << endl;

    return 0;
}

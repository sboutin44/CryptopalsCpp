/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <string>
#include <cassert>
#include <cstring>

#include <base64.hpp>


uint8_t* myXOR(uint8_t* a, uint8_t* b, int size)
{
    uint8_t* c = new uint8_t[size];

    for (int i=0;i<size;i++)
        c[i] = a[i]^b[i];

    return c;
}

int main() {

    // Sources of the inputs:
    // https://en.wikipedia.org/wiki/Base64

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

    // Base64 Encoding Tests
    res1 = base64Encode(input_1,strlen(input_1));
    res2 = base64Encode(input_2,strlen(input_2));
    res3 = base64Encode(input_3,strlen(input_3));
    res4 = base64Encode(input_4,strlen(input_4));
    res5 = base64Encode(input_5,strlen(input_5));
    res6 = base64Encode(input_6,strlen(input_6));
    res7 = base64Encode(input_7,strlen(input_7));
    res8 = base64Encode(input_8,strlen(input_8));
    res9 = base64Encode(input_9,strlen(input_9));
    res10 = base64Encode(input_10,strlen(input_10));

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

    // Base64 Decoding Tests
    uint8_t* decoded;
    decoded = base64Decode(expected_output_1,strlen(expected_output_1));
    assert(strcmp(input_1,(char*) decoded) == 0);

    decoded = base64Decode(expected_output_2,strlen(expected_output_2));
    assert(strcmp(input_2,(char*) decoded) == 0);

    decoded = base64Decode(expected_output_3,strlen(expected_output_3));
    assert(strcmp(input_3,(char*) decoded) == 0);

    decoded = base64Decode(expected_output_4,strlen(expected_output_4));
    assert(strcmp(input_4,(char*) decoded) == 0);

    decoded = base64Decode(expected_output_5,strlen(expected_output_5));
    assert(strcmp(input_5,(char*) decoded) == 0);

    decoded = base64Decode(expected_output_6,strlen(expected_output_6));
    assert(strcmp(input_6,(char*) decoded) == 0);

    decoded = base64Decode(expected_output_7,strlen(expected_output_7));
    assert(strcmp(input_7,(char*) decoded) == 0);

    decoded = base64Decode(expected_output_8,strlen(expected_output_8));
    assert(strcmp(input_8,(char*) decoded) == 0);

    decoded = base64Decode(expected_output_9,strlen(expected_output_9));
    assert(strcmp(input_9,(char*) decoded) == 0);

    char* result = base64Encode(challenge,size_challenge);
    assert(strcmp(result,expected) == 0);

    cout << result << endl;

    return 0;
}
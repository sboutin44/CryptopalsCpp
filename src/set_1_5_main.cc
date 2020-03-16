// Example program
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include "lib.h"
using namespace std;


void repeatedKeyXor (
    const char* input,
    const char* key,
    char* output)
{
    int inputSize = strlen(input);
    int keySize = strlen(key);

    ///////////////////////////////////
    // xor
    ///////////////////////////////////
    cout << inputSize << endl;
    for (int i=0 ; i<inputSize ; i++){
        output[i] = input[i] ^ key[i%keySize];
    }
    output[inputSize] = '\0';
}

int main()
{
    const char* a = "Burning 'em, if you ain't quick and nimbled I go crazy when I hear a cymbal";
    const char* b = "I go crazy when I hear a cymbal";
    const char* expected_encrypted_a = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272";
    const char* expected_encrypted_b = "a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
    const char* key = "ICE";
    char* output;

    uint8_t* expected_encrypted_a_hex = new uint8_t[strlen(expected_encrypted_a)/2];
    uint8_t* expected_encrypted_b_hex = new uint8_t[strlen(expected_encrypted_b)/2];
    hexDecode(expected_encrypted_a,expected_encrypted_a_hex);
    hexDecode(expected_encrypted_b,expected_encrypted_b_hex);

    // output = new char[strlen(a)];
    // repeatedKeyXor(a,key,output);
    // for (int i=0;i<strlen(a);i++)
    //     printf("%02x",output[i]);
    // delete[] output;

    output = new char[strlen(b)];
    repeatedKeyXor(b,key,output);
    cout << hex;
    cout << output;
    delete[] output;

}



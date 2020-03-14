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
#include <fstream>

#include "lib.h"

using namespace std;

#include "dictionnary.cpp"

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

int occurence(const char* s, char myChar )
{
    int occ = 0;
    char current = s[0];
    int i=0;
    while (current != '\0')
    {
        if (current == myChar)
            occ++;
        current = s[i+1];
        i++;
    }
    return occ;
}

float frequency(const char* s,char c)
{
    if (occurence(s,c) == 0) {
        return 0;
    }
    else {
        return (float) strlen(s) / (float) occurence(s,c) ;
    }
}

float frequencyCheck(const char* s)
{
    string sentence(s); // to use the find function.

    int deltas[8]; // Store deltas of the 8th most frequent letters in english.

    deltas[0] = frequency(s,'e') - 12.02;
    deltas[1] = frequency(s,'t') - 9.10;
    deltas[2] = frequency(s,'a') - 8.12;
    deltas[3] = frequency(s,'o') - 7.68;
    deltas[4] = frequency(s,'i') - 7.31;
    deltas[5] = frequency(s,'n') - 6.95;
    deltas[6] = frequency(s,'s') - 6.28;
    deltas[7] = frequency(s,'r') - 6.02;

    int sum = 0;
    for (int i=0;i<8;i++)
        sum += deltas[i];

    return sum;
}




void repeatedKeyXor (
    const char* input,
    const char* key,
    int         inputSize,
    int         keySize,
    const       char* output)
{
    // Expand the key to the size of the input.
    char* expandedKey = new char[inputSize];
    for (int i=0; i<=(inputSize%keySize);i+=keySize)
        strcpy(expandedKey+i,key);

    cout << expandedKey << endl;
}


int main()
{

    return 0;
}

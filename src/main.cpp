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

#include "base64.hpp"

using namespace std;

#include "dictionnary.cpp"

void quickEnglishChecker(uint8_t* sentence)
{
    string word;
    string sentence_string((char*) sentence); // pour utiliser la fonction find

    int score = 0;

    // {}
    int j=0;
    while (j< 118)
    {
        word = dictionnary[j];
        if (sentence_string.find(word) != string::npos)
            score++;
        j++;
    }

    if (score > 2) // si le score est égal à 0 ça sert à rien d'afficher.
    {
        cout << score << endl;
        cout << sentence << endl;
    }
}


int main()
{
    cout << "============================" << endl;
    cout << "Base64 encoding:" << endl;
    test_base64();

    cout << "============================" << endl;
    cout << "Fixed XOR" << endl;
    uint8_t a[] = {0x1c,0x01,0x11,0x00,0x1f,0x01,0x01,0x00,0x06,0x1a,0x02,0x4b,0x53,0x53,0x50,0x09,0x18,0x1c};
    uint8_t b[] = {0x68,0x69,0x74,0x20,0x74,0x68,0x65,0x20,0x62,0x75,0x6c,0x6c,0x27,0x73,0x20,0x65,0x79,0x65};

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    uint8_t* c = myXOR( a, b, sizeof(a));
    cout << "c: " << c << endl;
    cout << "============================" << endl;

    cout << "Single-byte XOR cipher" << endl;
    uint8_t toDecrypt[] = {0x1b,0x37,0x37,0x33,0x31,0x36,0x3f,0x78,0x15,0x1b,0x7f,0x2b,0x78,0x34,0x31,0x33,0x3d,0x78,0x39,0x78,0x28,0x37,0x2d,0x36,0x3c,0x78,0x37,0x3e,0x78,0x3a,0x39,0x3b,0x37,0x36};

    cout << "toDecrypt: " << toDecrypt << endl;
    uint8_t* key_array = new uint8_t[sizeof(toDecrypt)];

    // Brut force attack
    for (uint8_t key=0;key<=0xFF;key++) {
        memset(key_array, key, sizeof(toDecrypt));
        c = myXOR(toDecrypt,key_array,sizeof(toDecrypt));
        quickEnglishChecker(c);
        //cout << c << endl;
    }
    cout << "============================" << endl;

    return 0;
}

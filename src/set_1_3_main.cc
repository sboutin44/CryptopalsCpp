/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <string>
#include <cassert>
#include <cstring>
#include "lib.h"
using namespace std;


int main()
{
    cout << "\n============================" << endl;
    cout << "Set 1   Challenge 3" << endl;
    cout << "Detect single-character XOR" << endl;

    uint8_t* c;
    uint8_t toDecrypt[] = {0x1b,0x37,0x37,0x33,0x31,0x36,0x3f,0x78,0x15,0x1b,0x7f,0x2b,0x78,0x34,0x31,0x33,0x3d,0x78,0x39,0x78,0x28,0x37,0x2d,0x36,0x3c,0x78,0x37,0x3e,0x78,0x3a,0x39,0x3b,0x37,0x36};

    cout << "toDecrypt: " << toDecrypt << endl;
    uint8_t* key_array = new uint8_t[sizeof(toDecrypt)];

    // Brut force attack
    for (uint8_t key=0;key<=0xFE;key++)
    /*
        Si on va jusqu'au cas où key=0xFF, en incrémentant on va se
        retrouver avec key=0 car key est codé sur 1 octet,
        et on va boucler à l'infini, donc on
        traite le cas 0xFF à part.
     */
    {
        memset(key_array, key, sizeof(toDecrypt));
        c = myXOR(toDecrypt,key_array,sizeof(toDecrypt));
        quickEnglishChecker(c);
    }

    // Cas de key = 0xFF
    memset(key_array, 0xFF, sizeof(toDecrypt));
    c = myXOR(toDecrypt,key_array,sizeof(toDecrypt));
    quickEnglishChecker(c);

    //
    singlebyteXORattack(toDecrypt, sizeof(toDecrypt) );
}
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

    load_dictionary("google_10000_english.txt");
    singlebyteXORattack(toDecrypt, sizeof(toDecrypt) );
}
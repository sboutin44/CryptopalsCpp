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


int main()
{
    cout << "Fixed XOR" << endl;
    uint8_t a[] = {0x1c,0x01,0x11,0x00,0x1f,0x01,0x01,0x00,0x06,0x1a,0x02,0x4b,0x53,0x53,0x50,0x09,0x18,0x1c};
    uint8_t b[] = {0x68,0x69,0x74,0x20,0x74,0x68,0x65,0x20,0x62,0x75,0x6c,0x6c,0x27,0x73,0x20,0x65,0x79,0x65};

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;

    uint8_t* c = myXOR( a, b, sizeof(a));
    cout << "c: " << c << endl;

    return 0;
}

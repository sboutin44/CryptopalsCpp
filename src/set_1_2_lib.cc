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

uint8_t* myXOR(uint8_t* a, uint8_t* b, int size)
{
    uint8_t* c = new uint8_t[size];

    for (int i=0;i<size;i++)
        c[i] = a[i]^b[i];

    return c;
}

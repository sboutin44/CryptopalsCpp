/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "lib.h"

int hammingDistance(const char* a, const char* b)
{
    assert(strlen(a) == strlen(b));
    uint8_t byte;
    int distance = 0;
    
    for (int i=0; i = strlen(a) ; i++)
    {
        byte = a[i] ^ b[i];
        
        int j=0;
        while (j<8)
        {
            distance += (byte >> j) & 1;
        }
    }
    return distance;
}
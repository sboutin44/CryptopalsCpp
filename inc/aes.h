#ifndef CRYPTOPALS_INC_AES_H_
#define CRYPTOPALS_INC_AES_H_

#include <iostream>
#include <cstdlib>
#include <cstring>

typedef unsigned char byte;

void expandKey();

// AES functions
void addRoundKey(byte* state, byte* round_key);
void shiftRows();
void mixColumns(byte* state);
void subBytes(byte* state);

// invAES functions
void invShiftRows();
void invMixColumns();
void invSubBytes();


#endif //CRYPTOPALS_INC_AES_H_

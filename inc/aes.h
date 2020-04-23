// Copyright © 2020 Sebastien BOUTIN
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
// Except as contained in this notice, the name(s) of the above copyright
// holders shall not be used in advertising or otherwise to promote the sale,
// use or other dealings in this Software without prior written authorization.

#ifndef CRYPTOPALS_INC_AES_H_
#define CRYPTOPALS_INC_AES_H_

#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>

typedef uint8_t byte;

byte xtime(byte b);
byte GF8Mul(byte a, byte b);
void mixColumns_(byte* state, byte* matrix);

// AES
void AES128(byte* in, byte* key, byte* out);
void invAES128(byte* in, byte* key, byte* out);
void cipher(byte* in, byte* out, byte* w, int Nr);
void invCipher(byte* in, byte* out, byte* w, int Nr);
void KeyExpansion(byte* key, byte* w, int Nk);

// AES internal functions
void addRoundKey(byte* state, byte* round_key);
void subBytes(byte* state);
void shiftRows(byte* state);
void mixColumns(byte* state);

// invAES functions
void invMixColumns(byte* state);
void invShiftRows(byte* state);
void invSubBytes(byte* state);

// KeyExpansion
void rotWord(byte* word);
byte Rcon(int i);
void subWord(byte* word);

// Miscellaneous
void printWord(byte* word);
void printState();
void print16BytesBlock(byte* block);

#endif  // CRYPTOPALS_INC_AES_H_

// Copyright © 2020 Sebastien BOUTIN
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// Except as contained in this notice, the name(s) of the above copyright
// holders shall not be used in advertising or otherwise to promote the sale,
// use or other dealings in this Software without prior written authorization.

#ifndef CRYPTOPALS_INC_BLOCK_CIPHERS_H_
#define CRYPTOPALS_INC_BLOCK_CIPHERS_H_

#include "aes.h"
#include "types.h"

int PKCS7_getSize(byte* input, int len);
int PKCS7_getPaddingSize(byte* padded_input, int len);
int AES128_ECB_getCiphertextSize(byte* input, int len);
int AES128_CBC_getCiphertextSize(byte* input, int len);
byte* AES128_ECB_allocate(byte* input, int len);
byte* AES128_CBC_allocate(byte* input, int len);
void PKCS7_padding(byte* in, int lenIn, byte* out, int blocksize);
void AES128_ECB_decrypt(byte* ciphertext, byte* key, int len, byte* plaintext);
void AES128_ECB_encrypt(byte* plaintext, byte* key, int len, byte* ciphertext);
void AES128_CBC_encrypt(byte* plaintext, byte* key, const byte* IV,
                        byte* ciphertext, int len);
void AES128_CBC_decrypt(byte* ciphertext, byte* key, const byte* IV,
                        byte* plaintext, int len);

#endif  // CRYPTOPALS_INC_BLOCK_CIPHERS_H_
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

#include "block_ciphers.h"

#include "aes.h"

using namespace std;

int PKCS7_getSize(byte* input, int len) {
  int blocksize = AES128_BLOCKSIZE;
  int pad_len = blocksize - len % blocksize;
  return len + pad_len;
}

int AES128_ECB_getCiphertextSize(byte* input, int len) {
  return PKCS7_getSize(input, len);
}

int AES128_CBC_getCiphertextSize(byte* input, int len) {
  return PKCS7_getSize(input, len);
}

byte* AES128_ECB_allocate(byte* input, int len) {
  /* Allocate an array to contain the encrypted text of input */

  int blocksize = 16;
  int pad_len = blocksize - len % blocksize;
  int len_out = len + pad_len;
  byte* buffer = new byte[len_out];

  return buffer;
}

byte* AES128_CBC_allocate(byte* input, int len) {
  return AES128_ECB_allocate(input, len);
}

void PKCS7_padding(byte* in, int lenIn, byte* out, int blocksize) {
  /** Add padding to a pre-allocated array. */

  int pad_len = blocksize - lenIn % blocksize;
  byte pad_byte = pad_len;

  memcpy(out, in, lenIn);
  for (int i = 0; i < pad_len; i++) out[lenIn + i] = pad_byte;
}

void AES128_ECB_decrypt(byte* ciphertext, byte* key, int len, byte* plaintext) {
  /** Decrypt an AES encrypted bytes string with ECB mode. */

  int block_size = 16;

  for (int i = 0; i < len; i += block_size) {
    invAES128(&ciphertext[i], key, &plaintext[i]);
  }
}

void AES128_ECB_encrypt(byte* plaintext, byte* key, int plain_len,
                        byte* ciphertext) {
  /** Decrypt an AES encrypted bytes string with ECB mode. */

  int block_size = 16;

  for (int i = 0; i < plain_len; i += block_size) {
    AES128(&plaintext[i], key, &ciphertext[i]);
  }
}

void AES128_CBC_encrypt(byte* plaintext, byte* key, const byte* IV,
                        byte* ciphertext, int len) {
  /**
   *
   * @param plaintext  Padded text to encrypt.
   * @param ciphertext Encrypted plaintext.
   * @param len Length of both ciphetext and plaintext
   */

  int blocksize = 16;
  byte* buffer = new byte[len];

  // First block
  for (int j = 0; j < blocksize; j++) buffer[j] = IV[j] ^ plaintext[j];
  // for (int j = 0; j < len; j++) printf("%c ", buffer[j]);
  AES128(buffer, key, ciphertext);

  for (int i = blocksize; i < len; i += blocksize) {
    // XOR with previous block
    for (int j = 0; j < blocksize; j++)
      buffer[i + j] = ciphertext[i - blocksize + j] ^ plaintext[i + j];

    AES128(&buffer[i], key, &ciphertext[i]);
  }
  delete[] buffer;
}

void AES128_CBC_decrypt(byte* ciphertext, byte* key, const byte* IV,
                        byte* plaintext, int len) {
  int blocksize = 16;
  byte* buffer = new byte[len];

  for (int i = len - blocksize; i >= blocksize; i -= blocksize) {
    invAES128(&ciphertext[i], key, &buffer[i]);

    // XOR with previous block
    for (int j = 0; j < blocksize; j++)
      plaintext[i + j] = ciphertext[i - blocksize + j] ^ buffer[i + j];
  }

  invAES128(ciphertext, key, buffer);

  // First block
  for (int j = 0; j < blocksize; j++) plaintext[j] = IV[j] ^ buffer[j];

  delete[] buffer;
}

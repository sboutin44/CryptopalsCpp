// Copyright � 2020 Sebastien BOUTIN
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

#include "lib.h"
using namespace std;

bytearray_t* AES_CTR_enc(bytearray_t* plain, byte* key) {
  bytearray_t* ciphertext = new bytearray_t;

  ciphertext = AES_CTR_dec(plain, key);

  return ciphertext;
}

bytearray_t* AES_CTR_dec(bytearray_t* ciphertext, byte* key) {
  assert(ciphertext->l != 0);

  bytearray_t* keystream = new bytearray_t;
  bytearray_t* plain = new bytearray_t;
  plain->data_ptr = new byte[ciphertext->l];
  plain->l = ciphertext->l;

  keystream = getKeystream(ciphertext, key);

  // Decipher
  for (int i = 0; i < ciphertext->l; i++)
    plain->data_ptr[i] = ciphertext->data_ptr[i] ^ keystream->data_ptr[i];

  return plain;
}

bytearray_t* getKeystream(bytearray_t* plain, byte* key) {
  // nc := nounce || counter (= a block of 16 bytes in the keystream)
  byte* nc = new byte[AES_128_BLOCKSIZE];
  memset(nc, 0, AES_128_BLOCKSIZE);
  unsigned long long max_counter =
      (unsigned long long)plain->l / AES_128_BLOCKSIZE + 1;
  int l_keystream = max_counter * AES_128_BLOCKSIZE;
  byte* keystream = new byte[l_keystream];
  memset(keystream, 0, l_keystream);

  for (unsigned long long counter = 0; counter < max_counter; counter++) {
    // Concatenate the nounce and counter.
    // See https://cryptopals.com/sets/3/challenges/18 for the details.
    nc[8] = counter & 0xFF;
    nc[9] = (counter & 0xFF00) >> 8;
    nc[10] = (counter & 0xFF0000) >> 8 * 2;
    nc[11] = (counter & 0xFF000000) >> 8 * 3;
    nc[12] = (counter & 0xFF00000000) >> 8 * 4;
    nc[13] = (counter & 0xFF0000000000) >> 8 * 5;
    nc[14] = (counter & 0xFF000000000000) >> 8 * 6;
    nc[15] = (counter & 0xFF00000000000000) >> 8 * 7;

    AES128(nc, key, keystream + (16 * counter));
  }

  // Return the keystream as a bytearray_t.
  bytearray_t* keystream2 = new bytearray_t;
  keystream2->data_ptr = keystream;
  keystream2->l = l_keystream;

  return keystream2;
}

void challenge_18() {
  // Implement AES CTR mode.
  cout << "Challenge 18" << endl;

  const char* plainBased64Encoded =
      "L77na/nrFsKvynd6HzOoG7GHTLXsTVu9qvY/2syLXzhPweyyMTJULu/6/"
      "kXX0KSvoOLSFQ==";
  const char* key = "YELLOW SUBMARINE";

  // Base64 decode (to get the ciphertext)
  bytearray_t* c = new bytearray_t();
  c->l = getDecodedTextSize((uint8_t*)plainBased64Encoded,
                            strlen(plainBased64Encoded));
  assert(c->l != 0);
  c->data_ptr = new byte[c->l];
  base64Decode((uint8_t*)plainBased64Encoded, c->l, c->data_ptr);

  // D
  bytearray_t* plain;
  plain = AES_CTR_dec(c, (byte*)key);

  cout << plain->data_ptr << endl;

  // test the encryption function
  bytearray_t* expected_ciphertext = AES_CTR_enc(plain, (byte*)key);
  assert(memcmp(c->data_ptr, expected_ciphertext->data_ptr, c->l) == 0);
}
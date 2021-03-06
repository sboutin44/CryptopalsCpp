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

#include "aes.h"
#include "lib.h"
using namespace std;

void testRotWord() {
  byte word[] = {0x09, 0xcf, 0x4f, 0x3c};
  rotWord(word);
  byte expected[] = {0xcf, 0x4f, 0x3c, 0x09};
  assert(memcmp(expected, word, 4) == 0);
}

void testSubWord() {
  byte word[] = {0xcf, 0x4f, 0x3c, 0x09};
  subWord(word);
  byte expected[] = {0x8a, 0x84, 0xeb, 0x01};
  assert(memcmp(expected, word, 4) == 0);
}

void testRcon() {
  byte r = 0;
  int Nr = 10;
  for (int i = 1; i < Nr; i++) {
    r = Rcon(i);
    printf("%02x \n", r);
  }
}

// tests
void testXtime() {
  assert(xtime(0x57) == 0xae);
  assert(xtime(0xae) == 0x47);
  assert(xtime(0x47) == 0x8e);
  assert(xtime(0x8e) == 0x07);
}

void testKeyExpansion() {
  // AES 128: Nk = 4   Nb = 4  Nr = 10
  int Nb = 128 / 32;
  int Nr = 10;
  int Nk = 4;
  byte* w = new byte[Nb * (Nr + 1)];
  byte key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
  KeyExpansion(key, w, Nk);

  delete[] w;
}

void testMult() { assert(GF8Mul(0x57, 0x13) == 0xfe); }

void testAES128() {
  /** Test the AES-128 primitive.
   *
   * This pretty limited test is enought for the purpose of Cryptopals.
   * Samples are encrypted then decrypted.
   *
   * Samples vectors can be found in the doc FIPS 197 and here:
   * https://csrc.nist.gov/Projects/cryptographic-algorithm-validation-program/Block-Ciphers#AES
   * Extract from the file ECBGFSbox128.rsp.
   */

  int Nb = 128 / 32;

  // FIPS 197 samples
  byte in[] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d,
               0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
  byte key1[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6,
                 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
  byte expected[] = {0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb,
                     0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32};
  byte* out = new byte[4 * Nb];

  AES128(in, key1, out);
  assert(memcmp(expected, out, 4 * Nb) == 0);
  delete[] out;

  byte in2[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
  byte key2[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
  byte expected2[] = {0x69, 0xc4, 0xe0, 0xd8, 0x6a, 0x7b, 0x04, 0x30,
                      0xd8, 0xcd, 0xb7, 0x80, 0x70, 0xb4, 0xc5, 0x5a};
  byte* out2 = new byte[4 * Nb];

  AES128(in2, key2, out2);
  assert(memcmp(expected2, out2, 4 * Nb) == 0);
  delete[] out2;

  // Next are samples from:
  // https://csrc.nist.gov/Projects/cryptographic-algorithm-validation-program/Block-Ciphers#AES

  //--------------------------------------------------------------------
  // Sample test 1
  //--------------------------------------------------------------------
  const char* KEY = "00000000000000000000000000000000";
  const char* PLAINTEXT = "f34481ec3cc627bacd5dc3fb08f273e6";
  const char* CIPHERTEXT = "0336763e966d92595a567cc9ce537f5e";

  byte* plaintext = new byte[4 * Nb];
  byte* key = new byte[4 * Nb];
  byte* ciphertext = new byte[4 * Nb];
  byte* my_ciphertext = new byte[4 * Nb];
  byte* my_plaintext = new byte[4 * Nb];

  // Parse the string into hex array:
  // "ABCDEF" becomes {0xAB, 0xDC, 0xEF}
  hexDecode(PLAINTEXT, plaintext);
  hexDecode(KEY, key);
  hexDecode(CIPHERTEXT, ciphertext);

  // Encrypt
  AES128(plaintext, key, my_ciphertext);
  assert(memcmp(ciphertext, my_ciphertext, 4 * Nb) == 0);

  // Decrypt
  invAES128(ciphertext, key, my_plaintext);
  assert(memcmp(plaintext, my_plaintext, 4 * Nb) == 0);

  //--------------------------------------------------------------------
  // Sample test 2
  //--------------------------------------------------------------------
  // [ENCRYPT] then [DECRYPT]

  KEY = "00000000000000000000000000000000";
  PLAINTEXT = "f34481ec3cc627bacd5dc3fb08f273e6";
  CIPHERTEXT = "0336763e966d92595a567cc9ce537f5e";

  // Cleaning
  memset(plaintext, 0, 4 * Nb);
  memset(key, 0, 4 * Nb);
  memset(ciphertext, 0, 4 * Nb);
  memset(my_ciphertext, 0, 4 * Nb);
  memset(my_plaintext, 0, 4 * Nb);

  // Parse the string into hex array:
  // "ABCDEF" becomes {0xAB, 0xDC, 0xEF}
  hexDecode(PLAINTEXT, plaintext);
  hexDecode(KEY, key);
  hexDecode(CIPHERTEXT, ciphertext);

  // Encrypt
  AES128(plaintext, key, my_ciphertext);
  assert(memcmp(ciphertext, my_ciphertext, 4 * Nb) == 0);

  // Decrypt
  invAES128(ciphertext, key, my_plaintext);
  assert(memcmp(plaintext, my_plaintext, 4 * Nb) == 0);

  //--------------------------------------------------------------------
  // Sample test 3
  //--------------------------------------------------------------------
  // [ENCRYPT] then [DECRYPT]

  KEY = "00000000000000000000000000000000";
  PLAINTEXT = "f34481ec3cc627bacd5dc3fb08f273e6";
  CIPHERTEXT = "0336763e966d92595a567cc9ce537f5e";

  // Cleaning
  memset(plaintext, 0, 4 * Nb);
  memset(key, 0, 4 * Nb);
  memset(ciphertext, 0, 4 * Nb);
  memset(my_ciphertext, 0, 4 * Nb);
  memset(my_plaintext, 0, 4 * Nb);

  // Parse the string into hex array:
  // "ABCDEF" becomes {0xAB, 0xDC, 0xEF}
  hexDecode(PLAINTEXT, plaintext);
  hexDecode(KEY, key);
  hexDecode(CIPHERTEXT, ciphertext);

  // Encrypt
  AES128(plaintext, key, my_ciphertext);
  assert(memcmp(ciphertext, my_ciphertext, 4 * Nb) == 0);

  // Decrypt
  invAES128(ciphertext, key, my_plaintext);
  assert(memcmp(plaintext, my_plaintext, 4 * Nb) == 0);

  //--------------------------------------------------------------------
  // Sample test 3
  //--------------------------------------------------------------------
  // [ENCRYPT] then [DECRYPT]

  KEY = "00000000000000000000000000000000";
  PLAINTEXT = "9798c4640bad75c7c3227db910174e72";
  CIPHERTEXT = "a9a1631bf4996954ebc093957b234589";

  // Cleaning
  memset(plaintext, 0, 4 * Nb);
  memset(key, 0, 4 * Nb);
  memset(ciphertext, 0, 4 * Nb);
  memset(my_ciphertext, 0, 4 * Nb);
  memset(my_plaintext, 0, 4 * Nb);

  // Parse the string into hex array:
  // "ABCDEF" becomes {0xAB, 0xDC, 0xEF}
  hexDecode(PLAINTEXT, plaintext);
  hexDecode(KEY, key);
  hexDecode(CIPHERTEXT, ciphertext);

  // Encrypt
  AES128(plaintext, key, my_ciphertext);
  assert(memcmp(ciphertext, my_ciphertext, 4 * Nb) == 0);

  // Decrypt
  invAES128(ciphertext, key, my_plaintext);
  assert(memcmp(plaintext, my_plaintext, 4 * Nb) == 0);

  //--------------------------------------------------------------------
  // Sample test 4
  //--------------------------------------------------------------------
  // [ENCRYPT] then [DECRYPT]

  KEY = "00000000000000000000000000000000";
  PLAINTEXT = "96ab5c2ff612d9dfaae8c31f30c42168";
  CIPHERTEXT = "ff4f8391a6a40ca5b25d23bedd44a597";

  // Cleaning
  memset(plaintext, 0, 4 * Nb);
  memset(key, 0, 4 * Nb);
  memset(ciphertext, 0, 4 * Nb);
  memset(my_ciphertext, 0, 4 * Nb);
  memset(my_plaintext, 0, 4 * Nb);

  // Parse the string into hex array:
  // "ABCDEF" becomes {0xAB, 0xDC, 0xEF}
  hexDecode(PLAINTEXT, plaintext);
  hexDecode(KEY, key);
  hexDecode(CIPHERTEXT, ciphertext);

  // Encrypt
  AES128(plaintext, key, my_ciphertext);
  assert(memcmp(ciphertext, my_ciphertext, 4 * Nb) == 0);

  // Decrypt
  invAES128(ciphertext, key, my_plaintext);
  assert(memcmp(plaintext, my_plaintext, 4 * Nb) == 0);

  //--------------------------------------------------------------------
  // Sample test 5
  //--------------------------------------------------------------------
  // [ENCRYPT] then [DECRYPT]

  KEY = "00000000000000000000000000000000";
  PLAINTEXT = "6a118a874519e64e9963798a503f1d35";
  CIPHERTEXT = "dc43be40be0e53712f7e2bf5ca707209";

  // Cleaning
  memset(plaintext, 0, 4 * Nb);
  memset(key, 0, 4 * Nb);
  memset(ciphertext, 0, 4 * Nb);
  memset(my_ciphertext, 0, 4 * Nb);
  memset(my_plaintext, 0, 4 * Nb);

  // Parse the string into hex array:
  // "ABCDEF" becomes {0xAB, 0xDC, 0xEF}
  hexDecode(PLAINTEXT, plaintext);
  hexDecode(KEY, key);
  hexDecode(CIPHERTEXT, ciphertext);

  // Encrypt
  AES128(plaintext, key, my_ciphertext);
  assert(memcmp(ciphertext, my_ciphertext, 4 * Nb) == 0);

  // Decrypt
  invAES128(ciphertext, key, my_plaintext);
  assert(memcmp(plaintext, my_plaintext, 4 * Nb) == 0);

  //--------------------------------------------------------------------
  // Sample test 6
  //--------------------------------------------------------------------
  // [ENCRYPT] then [DECRYPT]

  KEY = "00000000000000000000000000000000";
  PLAINTEXT = "cb9fceec81286ca3e989bd979b0cb284";
  CIPHERTEXT = "92beedab1895a94faa69b632e5cc47ce";

  // Cleaning
  memset(plaintext, 0, 4 * Nb);
  memset(key, 0, 4 * Nb);
  memset(ciphertext, 0, 4 * Nb);
  memset(my_ciphertext, 0, 4 * Nb);
  memset(my_plaintext, 0, 4 * Nb);

  // Parse the string into hex array:
  // "ABCDEF" becomes {0xAB, 0xDC, 0xEF}
  hexDecode(PLAINTEXT, plaintext);
  hexDecode(KEY, key);
  hexDecode(CIPHERTEXT, ciphertext);

  // Encrypt
  AES128(plaintext, key, my_ciphertext);
  assert(memcmp(ciphertext, my_ciphertext, 4 * Nb) == 0);

  // Decrypt
  invAES128(ciphertext, key, my_plaintext);
  assert(memcmp(plaintext, my_plaintext, 4 * Nb) == 0);

  //--------------------------------------------------------------------
  // Sample test 7
  //--------------------------------------------------------------------
  // [ENCRYPT] then [DECRYPT]

  KEY = "00000000000000000000000000000000";
  PLAINTEXT = "b26aeb1874e47ca8358ff22378f09144";
  CIPHERTEXT = "459264f4798f6a78bacb89c15ed3d601";

  // Cleaning
  memset(plaintext, 0, 4 * Nb);
  memset(key, 0, 4 * Nb);
  memset(ciphertext, 0, 4 * Nb);
  memset(my_ciphertext, 0, 4 * Nb);
  memset(my_plaintext, 0, 4 * Nb);

  // Parse the string into hex array:
  // "ABCDEF" becomes {0xAB, 0xDC, 0xEF}
  hexDecode(PLAINTEXT, plaintext);
  hexDecode(KEY, key);
  hexDecode(CIPHERTEXT, ciphertext);

  // Encrypt
  AES128(plaintext, key, my_ciphertext);
  assert(memcmp(ciphertext, my_ciphertext, 4 * Nb) == 0);

  // Decrypt
  invAES128(ciphertext, key, my_plaintext);
  assert(memcmp(plaintext, my_plaintext, 4 * Nb) == 0);

  //--------------------------------------------------------------------
  // Sample test 8
  //--------------------------------------------------------------------
  // [ENCRYPT] then [DECRYPT]

  KEY = "00000000000000000000000000000000";
  PLAINTEXT = "58c8e00b2631686d54eab84b91f0aca1";
  CIPHERTEXT = "08a4e2efec8a8e3312ca7460b9040bbf";

  // Cleaning
  memset(plaintext, 0, 4 * Nb);
  memset(key, 0, 4 * Nb);
  memset(ciphertext, 0, 4 * Nb);
  memset(my_ciphertext, 0, 4 * Nb);
  memset(my_plaintext, 0, 4 * Nb);

  // Parse the string into hex array:
  // "ABCDEF" becomes {0xAB, 0xDC, 0xEF}
  hexDecode(PLAINTEXT, plaintext);
  hexDecode(KEY, key);
  hexDecode(CIPHERTEXT, ciphertext);

  // Encrypt
  AES128(plaintext, key, my_ciphertext);
  assert(memcmp(ciphertext, my_ciphertext, 4 * Nb) == 0);

  // Decrypt
  invAES128(ciphertext, key, my_plaintext);
  assert(memcmp(plaintext, my_plaintext, 4 * Nb) == 0);

  // Decryptions
  byte* to_decrypt = expected2;
  byte* out3 = new byte[4 * Nb];

  invAES128(to_decrypt, key2, out3);
  assert(memcmp(out3, in2, 4 * Nb) == 0);
  delete[] out3;

  delete[] plaintext;
  delete[] key;
  delete[] ciphertext;
  delete[] my_plaintext;
  delete[] my_ciphertext;

  cout << "testAES128 \t\tpassed" << endl;
}

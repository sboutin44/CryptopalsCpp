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
using namespace std;

byte Sbox[] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b,
    0xfe, 0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 0xb7, 0xfd, 0x93, 0x26,
    0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2,
    0xeb, 0x27, 0xb2, 0x75, 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 0x53, 0xd1, 0x00, 0xed,
    0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f,
    0x50, 0x3c, 0x9f, 0xa8, 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 0xcd, 0x0c, 0x13, 0xec,
    0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14,
    0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 0xe7, 0xc8, 0x37, 0x6d,
    0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f,
    0x4b, 0xbd, 0x8b, 0x8a, 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11,
    0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f,
    0xb0, 0x54, 0xbb, 0x16};

byte invSbox[] = {
    0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e,
    0x81, 0xf3, 0xd7, 0xfb, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87,
    0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, 0x54, 0x7b, 0x94, 0x32,
    0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
    0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49,
    0x6d, 0x8b, 0xd1, 0x25, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16,
    0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, 0x6c, 0x70, 0x48, 0x50,
    0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
    0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05,
    0xb8, 0xb3, 0x45, 0x06, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02,
    0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, 0x3a, 0x91, 0x11, 0x41,
    0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
    0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8,
    0x1c, 0x75, 0xdf, 0x6e, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89,
    0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, 0xfc, 0x56, 0x3e, 0x4b,
    0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
    0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59,
    0x27, 0x80, 0xec, 0x5f, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d,
    0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef, 0xa0, 0xe0, 0x3b, 0x4d,
    0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63,
    0x55, 0x21, 0x0c, 0x7d};

int Nb = 128 / 32;
byte* state;

byte xtime(byte b) {
  unsigned int c = ((int)b) << 1;

  if ((c & 0x100)) c ^= 0x1b;

  return (byte)c;
}

byte GF8Mul(byte a, byte b) {
  byte aa = a;
  byte bb = b;
  byte r = 0;
  byte t;
  while (aa != 0) {
    if ((aa & 1) != 0) r = r ^ bb;
    t = bb & 0x80;
    bb = bb << 1;
    if (t != 0) bb = bb ^ 0x1b;
    aa = aa >> 1;
  }
  return r;
}

void addRoundKey(byte* state, byte* round_key) {
  for (int i = 0; i < 4 * Nb; i++) state[i] ^= round_key[i];
}

void shiftRows(byte* state) {
  byte tmp1 = state[5];
  byte tmp2 = state[9];
  byte tmp3 = state[13];
  byte tmp4 = state[1];

  state[1] = tmp1;
  state[5] = tmp2;
  state[9] = tmp3;
  state[13] = tmp4;

  tmp1 = state[2];
  tmp2 = state[6];
  tmp3 = state[10];
  tmp4 = state[14];

  state[2] = tmp3;
  state[6] = tmp4;
  state[10] = tmp1;
  state[14] = tmp2;

  tmp1 = state[3];
  tmp2 = state[7];
  tmp3 = state[11];
  tmp4 = state[15];

  state[3] = tmp4;
  state[7] = tmp1;
  state[11] = tmp2;
  state[15] = tmp3;
}

void mixColumns(byte* state) {
  byte matrix[] = {0x02, 0x03, 0x01, 0x01, 0x01, 0x02, 0x03, 0x01,
                   0x01, 0x01, 0x02, 0x03, 0x03, 0x01, 0x01, 0x02};

  mixColumns_(state, matrix);
}

void invMixColumns(byte* state) {
  byte matrix[] = {0x0e, 0x0b, 0x0d, 0x09, 0x09, 0x0e, 0x0b, 0x0d,
                   0x0d, 0x09, 0x0e, 0x0b, 0x0b, 0x0d, 0x09, 0x0e};

  mixColumns_(state, matrix);
}

void mixColumns_(byte* state, byte* matrix) {
  byte s;
  byte* word = new byte[4];  // Store computed values of mult.

  for (int col = 0; col < 4 * Nb; col += 4) {
    for (int i = 0; i < 4; i++) {
      s = 0;
      for (int j = 0; j < 4; j++)
        s ^= GF8Mul(matrix[4 * i + j], state[col + j]);
      word[i] = s;
    }
    memcpy(&state[col], word, 4);
  }

  delete[] word;
}

void subBytes(byte* state) {
  for (int i = 0; i < 4 * Nb; i++) state[i] = Sbox[state[i]];
}

void invShiftRows(byte* state) {
  shiftRows(state);
  shiftRows(state);
  shiftRows(state);
}

void invSubBytes(byte* state) {
  for (int i = 0; i < 4 * Nb; i++) state[i] = invSbox[state[i]];
}

void rotWord(byte* word) {
  byte tmp = word[0];

  word[0] = word[1];
  word[1] = word[2];
  word[2] = word[3];
  word[3] = tmp;
}

void subWord(byte* word) {
  for (int i = 0; i < 4; i++) word[i] = Sbox[word[i]];
}

byte Rcon(int i) {
  byte x = 2;

  if (i == 1) return 0x01;

  for (int j = 1; j < i - 1; j++) x = xtime(x);
  return x;
  // word[0] ^= rcon_i;
}

void KeyExpansion(byte* key, byte* w, int Nk) {
  int Nr;
  if (Nk == 4) Nr = 10;
  if (Nk == 6) Nr = 12;
  if (Nk == 8) Nr = 14;

  int i = 0;
  byte* temp = new byte[4];

  // Set first key 4*4 block with the initial key
  while (i < Nk) {
    for (int j = 0; j < 4; j++) {
      w[4 * i + j] = key[4 * i + j];
    }
    i = i + 1;
  }
  i = Nk;

  // Remaining blocks
  while (i < Nb * (Nr + 1)) {
    // Store w[i-1] (notation in FIPS-197)
    for (int j = 0; j < 4; j++) {
      temp[j] = w[4 * (i - 1) + j];
    }

    // Case when i = 0 mod 4]
    if (i % Nk == 0) {
      rotWord(temp);
      subWord(temp);
      temp[0] ^= Rcon(i / Nk);
    } else if (Nk > 6 && i % Nk == 4) {
      subWord(temp);
    }

    // XOR
    for (int j = 0; j < 4; j++) {
      w[4 * i + j] = w[4 * (i - Nk) + j] ^ temp[j];
    }
    i = i + 1;
  }
  delete[] temp;
}

void cipher(byte* in, byte* out, byte* w, int Nr) {
  /** Encryption cipher of the Advanced Encryption Standard.
   *
   * The calling function must allocate 16-bytes arrays for each parameters.
   *
   * @param in  Pre-allocated 16- bytes array with the plaintext.
   * @param out Pre-allocated 16-bytes for the ciphertext.
   * @param w   Vector pointing to the session keys.
   * @param Nr  Number of rounds.
   */

  // Allocate memory for the global varibale 'state'
  state = new byte[4 * Nb];
  memset(state, 0x00, 4 * Nb);  // TODO: remove when all tests passed.
  memcpy(state, in, 4 * Nb);

  addRoundKey(state, &w[0]);

  for (int round = 1; round < Nr; round++) {
    subBytes(state);
    shiftRows(state);
    mixColumns(state);
    addRoundKey(state, &w[4 * round * Nb]);
  }

  subBytes(state);
  shiftRows(state);
  addRoundKey(state, &w[4 * Nr * Nb]);

  memcpy(out, state, 4 * Nb);

  // Cleaning
  memset(state, 0x00, 4 * Nb);  // TODO: remove when all tests passed.
  delete[] state;
}

void invCipher(byte* in, byte* out, byte* w, int Nr) {
  /** Decryption cipher of the Advanced Encryption Standard.
   *
   * The calling function must allocate 16-bytes arrays for each parameters.
   *
   * @param in  Pre-allocated 16- bytes array with the plaintext.
   * @param out Pre-allocated 16-bytes for the ciphertext.
   * @param w   Vector pointing to the session keys.
   * @param Nr  Number of rounds.
   */

  // Allocate memory for the global varibale 'state'
  state = new byte[4 * Nb];
  memset(state, 0x00, 4 * Nb);  // TODO: remove when all tests passed.
  memcpy(state, in, 4 * Nb);

  addRoundKey(state, &w[4 * Nr * Nb]);

  for (int round = Nr - 1; round >= 1; round--) {
    invShiftRows(state);
    invSubBytes(state);
    addRoundKey(state, &w[4 * round * Nb]);
    invMixColumns(state);
  }
  invShiftRows(state);
  invSubBytes(state);
  addRoundKey(state, &w[0]);

  memcpy(out, state, 4 * Nb);

  // Cleaning
  memset(state, 0x00, 4 * Nb);  // TODO: remove when all tests passed.
  delete[] state;
}

void AES128(byte* in, byte* key, byte* out) {
  /** Advanced Encryption Standard encryption primitive.
   *
   * The calling function must allocate 16-bytes arrays for each parameters.
   *
   * @param in  Pre-allocated 16-bytes array with the plaintext.
   * @param key Pre-allocated 16-bytes array containing the key.
   * @param out Pre-allocated 16-bytes for the ciphertext.
   */

  // AES 128: Nk = 4   Nb = 4  Nr = 10
  int Nr = 10;
  int Nk = 4;
  byte* w = new byte[4 * Nb * (Nr + 1)];

  KeyExpansion(key, w, Nk);
  cipher(in, out, w, Nr);

  // Cleaning
  delete[] w;
}

void invAES128(byte* in, byte* key, byte* out) {
  /** Advanced Encryption Standard decryption primitive.
   *
   * The calling function must allocate 16-bytes arrays for each parameters.
   *
   * @param in  Pre-allocated 16-bytes array with the plaintext.
   * @param key Pre-allocated 16-bytes array containing the key.
   * @param out Pre-allocated 16-bytes for the ciphertext.
   */

  // AES 128: Nk = 4   Nb = 4  Nr = 10
  int Nr = 10;
  int Nk = 4;
  byte* w = new byte[4 * Nb * (Nr + 1)];

  KeyExpansion(key, w, Nk);
  invCipher(in, out, w, Nr);

  delete[] w;
}

// tools
void printWord(byte* word) {
  for (int i = 0; i < 4; i++) printf("%02x ", word[i]);
  printf("\n");
}

void print16BytesBlock(byte* block) {
  for (int i = 0; i < 4 * Nb; i++) printf("%02x ", block[i]);
  printf("\n");
}

void printState() {
  for (int i = 0; i < 4 * Nb; i++) printf("%02x ", state[i]);
  printf("\n");
}

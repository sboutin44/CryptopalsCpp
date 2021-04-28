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

#include "lib.h"
#include "tests.h"

using namespace std;

float absolute (float f){
  // Workaround to use the abs function on macOS with the error:
  // error: call to 'abs' is ambiguous”
  if (f < .0)
    f = -f;
  return f;
}

Oracle::Oracle() {
  key = new byte[16];  // Allocate a default AES128 key.
  randomAES128key(key);
  offset.l = 0;
  offset.data_ptr = nullptr;
}

void Oracle::addEntry(bytearray_t entry) { entries.push_back(entry); }

void Oracle::printEntries() {
  for (auto it = entries.begin(); it != entries.end(); it++) {
    bytearray_t entry = *it;
    printByteArray(entry.data_ptr, entry.l);
  }
}

int Oracle::size() { return entries.size(); }

int Oracle::getEntryDataLen(int pos) { return entries[pos].l; }

void Oracle::getEntryData(int pos, byte* dst) {
  memcpy(dst, entries[pos].data_ptr, entries[pos].l);
}

const byte* Oracle::getEntryData(int pos) { return entries[pos].data_ptr; }

void Oracle::printEntry(int pos) {
  if (pos < entries.size()) {
    cout << "len: " << entries[pos].l << endl;
    cout << "data: " << endl;
    for (int i = 0; i < entries.size(); i++)
      printf("%02x ", entries[pos].data_ptr[i]);
    cout << endl;
  } else {
    cout << "error: no entry at position " << pos << endl;
  }
}

void Oracle::setKey(byte* k, int len) { memcpy(key, k, len); }

const byte* Oracle::getKey() { return key; }

void randomAES128key(byte* empty_key) {
  int l = 16;
  byte v;

  for (int i = 0; i < l; i++) {
    v = rand() % 256;
    empty_key[i] = v;
  }
}

float similarBlocksDistanceRatio(const byte* input, int l) {
  /** Returns a ratio of Hamming distances computed between all 128-bit blocks.
   *
   * Ratio should be around 50% for an AES128-CBC encrypted input, and
   * significantly less if AES128-ECB encrypted.	 *
   */

  int block_size = 16;
  int hamming_distance = 0;
  int total_passes = 0;

  for (int j = 0; j < l; j += block_size) {
    for (int k = j + block_size; k < l; k += block_size) {
      hamming_distance += hammingDistance(&input[j], &input[k], block_size);
      total_passes++;
    }
  }
  return ((float)hamming_distance) / (float)(total_passes * 128);
}

ENCRYPTION_MODE guessEncryptionMode(const byte* input, int l) {
  float r = similarBlocksDistanceRatio(input, l);
  float thresold = 0.2;

  if (absolute(r - 0.50) < thresold)
    return CBC;
  else
    return ECB;
}

bool isAES128_CBC(const byte* input, int l) {
  if (guessEncryptionMode(input, l) == CBC)
    return true;
  else
    return false;
}

bool isAES128_ECB(const byte* input, int l) {
  if (guessEncryptionMode(input, l) == ECB)
    return true;
  else
    return false;
}

void Oracle::setOffsetType(OFFSET_TYPE ot) { offsetType = ot; }

std::vector<bytearray_t> Oracle::getEntries() { return entries; }

void Oracle::clear() { entries.clear(); }

void Oracle::setOffset(const char* s) {
  offset.l = strlen(s);
  if (offset.data_ptr != nullptr) delete[] offset.data_ptr;
  offset.data_ptr = new byte[offset.l];

  memcpy(offset.data_ptr, (byte*)s, offset.l);
}

void Oracle::printOffset() {
  cout << "offset.l : " << offset.l << endl;
  for (int i = 0; i < offset.l; i++) printf("%c", offset.data_ptr[i]);
  printf("\n");
}

void Oracle::printRealMode(int pos){
	assert(pos < this->size());
	if (enc_mode[pos] == ECB )
		cout  << "Real Mode: ECB" << endl;
	else if (enc_mode[pos] == CBC )
		cout  << "Real Mode: CBC" << endl;
	else
		cout << "Mode error" << endl;
}

// void Oracle::encryption_oracle(byte* input, int l_input, byte* key) {
void Oracle::encryption_oracle(byte* input, int l_input) {
  int len;
  byte* input_padded;

  if (offsetType == RANDOM) {
    // 2. padd before and after 5-10 bytes randomly
    // choose how many byte to pad
    int l_before = rand() % 6 + 5;
    int l_after = rand() % 6 + 5;
    len = l_before + l_input + l_after;
    input_padded = new byte[len];

    // Copy plaintext and pad with 5-10 random bytes
    memset(&input_padded[0], rand() % 256, l_before);
    memcpy(&input_padded[l_before], input, l_input);
    memset(&input_padded[l_before + l_input], rand() % 256, l_after);
  } else if (offsetType == FIXED) {
    // 2. pad with a fixed offset and fixed byte for tests purpose.
    int l_before = offset.l;
    len = l_before + l_input;
    input_padded = new byte[len];

    // Copy plaintext and pad with 5-10 random bytes
    memcpy(&input_padded[0], offset.data_ptr, l_before);
    memcpy(&input_padded[l_before], input, l_input);
  } else {
    len = l_input;
    input_padded = input;
  }

  // PKCS7 padding
  int blocksize = 16;
  int pad_len = blocksize - len % blocksize;
  int len_out = len + pad_len;
  byte* buffer = new byte[len_out];
  byte* ciphertext_CBC = new byte[len_out];
  byte* ciphertext_ECB = new byte[len_out];

  PKCS7_padding((byte*)input_padded, len, buffer, blocksize);

  // Create a new the entry to the Oracle
  bytearray_t entry;
  entry.l = len_out;
  entry.data_ptr = new byte[len_out];

  // 3. Choose ECB or CBC randomly
  int choice = rand() % 2;

  // 4. Encrypt
  if (choice == 0) {
    enc_mode.push_back(CBC);  // Keep track of the operation

    byte IV[16];
    randomAES128key(IV);

    AES128_CBC_encrypt(buffer, key, IV, ciphertext_CBC, len_out);
    memcpy(entry.data_ptr, ciphertext_CBC, len_out);
    addEntry(entry);
  } else {
    enc_mode.push_back(ECB);  // Keep track of the operation

    AES128_ECB_encrypt(buffer, key, len_out, ciphertext_ECB);

    memcpy(entry.data_ptr, ciphertext_ECB, len_out);
    addEntry(entry);
  }
}

void testGuessEncryptionMode() {
  srand(time(NULL));

  int nbEntries = 500;

  const char* input =
      "You can go in thYou can go in thYou can go in thYou can go in thYou can "
      "go in thYou can go in thYou can go in thYou can go in thYou can go in "
      "thYou can go in thYou can go in thYou can go in thYou can go in thYou "
      "can go in thYou can go in thYou can go in thYou can go in thYou can go "
      "in thYou can go in thYou can go in thYou can go in thYou can go in th";

  int l_input = strlen(input);

  Oracle oracle;

  // Feed the oracle with encrypted texts with randoom keys.
  for (int i = 0; i < nbEntries; i++)
    oracle.encryption_oracle((byte*)input, l_input);

  // Guess the encryption mode used for each entries, and verify them to result
  // computed during the call to encryption_oracle.
  for (int i = 0; i < nbEntries; i++) {
    byte* entry = new byte[oracle.getEntryDataLen(i)];
    oracle.getEntryData(i, entry);

    bool real_mode = oracle.enc_mode[i];
    bool guessed_mode = guessEncryptionMode(entry, oracle.getEntryDataLen(i));
    assert(real_mode == guessed_mode);

    if (real_mode == ECB) {
    	assert( isAES128_CBC(oracle.getEntryData(i),oracle.getEntryDataLen(i)) == false);
    	assert( isAES128_ECB(oracle.getEntryData(i),oracle.getEntryDataLen(i)) == true);
    } else if (real_mode == CBC) {
    	assert( isAES128_CBC(oracle.getEntryData(i),oracle.getEntryDataLen(i)) == true);
    	assert( isAES128_ECB(oracle.getEntryData(i),oracle.getEntryDataLen(i)) == false);
    }
  }
  cout << "testGuessEncryptionMode passed" << endl;
}

void challenge_11() {
  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 2" << endl;
  cout << "11. An ECB/CBC detection oracle" << endl;
  cout << "------------------------------------\n" << endl;

  // See test/tests_set2.cc
  testGuessEncryptionMode();
}

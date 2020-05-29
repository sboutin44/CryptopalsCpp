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

#include "Vector.h"
#include "lib.h"

using namespace std;

float similarBlocksDistanceRatio(byte* input, int l, int block_size) {
  /** Returns a ratio of Hamming distances computed between all 128-bit blocks.
   *
   * Ratio should be around 50% for an AES128-CBC encrypted input, and
   * significantly less if AES128-ECB encrypted.	 *
   */

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

// Alternative way to find the blocksize:
//  int maxBlocksize = 20;  // length in bytes
//  map<float, int> map_dist_to_size;
//  for (int blocksize = 10; blocksize < maxBlocksize; blocksize++) {
//    float r = similarBlocksDistanceRatio(ciphertext_ECB, len_out,
//    blocksize); map_dist_to_size[r] = blocksize;
//  }
//
//  cout << "Probable blocksize: " << map_dist_to_size.begin()->second <<
//  endl;

int detectOffsetLength(Oracle oracle, int blocksize) {
  /* Detect the size of the offset added by the oracle.
   *
   * Let's take an 8 bytes block size, in ECB mode if we encrypt 2 blocks of As,
   * and prefix it by Bs, at some point the As string will aligned with 2
   * blocks.
   *
   * plain:  	XXXXAAAA AAAAAAAA AAAACCCC
   * cipher: 	fdslfkjd samethin fdksajfs (not real values)
   * ...
   *
   * plain:		XXXXBBBBB AAAAAAAA AAAAAAAA CCCCCC
   * cipher:	fsagwgefg samethin samethin fsdreg
   * */

  // Create a string long enough to detect ECB.
  string middle =
      "AAAAAAAAAAAAAAAA"
      "AAAAAAAAAAAAAAAA"
      "CCCCCCCCCCCCCCCC"
      "CCCCCCCCCCCCCCCC"
      "CCCCCCCCCCCCCCCC"
      "CCCCCCCCCCCCCCCC"
      "CCCCCCCCCCCCCCCC"
      "CCCCCCCCCCCCCCCC"
      "CCCCCCCCCCCCCCCC"
      "CCCCCCCCCCCCCCCC"
      "CCCCCCCCCCCCCCCC"
      "CCCCCCCCCCCCCCCC"
      "CCCCCCCCCCCCCCCC"
      "CCCCCCCCCCCCCCCC";
  oracle.clear();
  int is_eq = 1;
  int len = 0;
  do {
    len++;
    string prefix(1, 'B');
    middle = prefix + middle;

    // Encrypt, ensuring we encrypt with ECB.
    oracle.encryption_oracle((byte*)middle.c_str(), middle.length());
    do {
      oracle.encryption_oracle((byte*)middle.c_str(), middle.length());
    } while (!isAES128_ECB(oracle.getCiphertext()->data_ptr,
                           oracle.getCiphertext()->l));

    bytearray_t ciphertext;
    ciphertext.l = oracle.getCiphertext()->l;
    ciphertext.data_ptr = new byte[ciphertext.l];
    memcpy(ciphertext.data_ptr, oracle.getCiphertext()->data_ptr, ciphertext.l);

    const byte* b1 = &ciphertext.data_ptr[blocksize];
    const byte* b2 = &ciphertext.data_ptr[2 * blocksize];
    is_eq = memcmp(b1, b2, blocksize);

  } while (is_eq != 0);

  return blocksize - len;
}

int detectBlockSize(Oracle& oracle) {
  // 1. Detect the block size: when we feed the oracle with bigger strings
  string test_string = "A";
  oracle.encryption_oracle((byte*)test_string.c_str(), test_string.length());
  int last_entry_pos = oracle.debug_size();
  int previous_len = oracle.getEntryDataLen(last_entry_pos - 1);
  int new_len = previous_len;

  while (previous_len == new_len) {
    // Add 'A' at the end
    string suffix(1, 'A');
    test_string = test_string + suffix;
    int l_input = test_string.length();

    oracle.encryption_oracle((byte*)test_string.c_str(), l_input);
    new_len = oracle.getCiphertext()->l;
  }

  int blocksize = abs(new_len - previous_len);
  return blocksize;
}

void challenge_12() {
  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 2" << endl;
  cout << "12. Byte-at-a-time ECB decryption (Simple)" << endl;
  cout << "------------------------------------\n" << endl;

  cout << std::boolalpha;  // Display booleans as true/false strings.
  srand(time(NULL));

  const char* unknown_string_b64 =
      "Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkg"
      "aGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBq"
      "dXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUg"
      "YnkK";

  // Decode the Base64 encoded string 'unknown_string_b64'.
  uint64_t size_encoded = strlen(unknown_string_b64);
  uint64_t unknown_string_len =
      getDecodedTextSize((byte*)unknown_string_b64, size_encoded);
  byte* unknown_string = new byte[unknown_string_len + 1];  // Add space for \0.
  base64Decode((byte*)unknown_string_b64, size_encoded, unknown_string);
  unknown_string[unknown_string_len] = '\0';  // TODO: make this simpler.
  string unknown_string_cpp_s((char*)unknown_string);

  /**************************************************************************
   * In the following section with break with the oracle the encrypted input,
   * and recover the unknown_string
   *************************************************************************/

  // 0. Set the oracle type.
  Oracle oracle;
  oracle.setOffsetType(FIXED);
  oracle.setOffset("XXXX");

  // 1. Detect the block size: when we feed the oracle with bigger strings
  int blocksize = detectBlockSize(oracle);
  cout << "Detected blocksize: " << blocksize << endl;

  // 2. Detect the encryption mode:
  bool char_found = false;
  string decrypted = "";

  // 3. Create plaintexts like AAAAAAAAAAAAAAAX, AAAAAAAAAAAAAAAX'...
  // where X, X', etc are letters.
  string block0 = "AAAAAAAAAAAA";     // Compensate the offset with 'A's.
  string block1 = "";                 // Additional blocks to detect ECB.
  string block2 = "AAAAAAAAAAAAAAA";  // Contain the secret byte at the end.

  int offset_len = detectOffsetLength(oracle, blocksize);
  cout << "Offset: ";
  cout << offset_len << endl;

  // Check our values are correct:
  assert(block0.length() == blocksize - offset_len);
  assert(block2.length() == 15);

  unknown_string_len = unknown_string_cpp_s.length();
  int remainging_len = unknown_string_len;
  bytearray_t target;

  while (remainging_len > 0) {
    // Create a 16*coef bytes long string, long enough to detect ECB mode:
    block1 = "";
    int target_nb_blocks = 100;
    for (int i = 0; i < (target_nb_blocks * 16 + 15); i++) {
      string c(1, 'A');
      block1 += c;
    }

    // The first char of unknown_string must be the last byte of a block.
    string plaintext =
        block0 + block1 +
        unknown_string_cpp_s.substr(unknown_string_len - remainging_len,
                                    unknown_string_len);

    // Encrypt, first attempt to get ECB.
    oracle.encryption_oracle((byte*)plaintext.c_str(), plaintext.length());

    // Retry while not ECB
    while (!isAES128_ECB(oracle.getCiphertext()->data_ptr,
                         oracle.getCiphertext()->l)) {
      oracle.encryption_oracle((byte*)plaintext.c_str(), plaintext.length());
    }

    // Save the encrypted text, this is our target for the matching attempts.
    target.l = oracle.getCiphertext()->l;
    target.data_ptr = new byte[target.l];
    memcpy(target.data_ptr, oracle.getCiphertext()->data_ptr, target.l);

    int unknown_char_pos =
        blocksize + target_nb_blocks * 16;  // Pos of x in AAAAAAAAAAAAAAAx

    // Encrypt all possible AAAAAAAAAAAAAAAx
    for (int X = 0; X <= 0xFF; X++) {
      string BBs = "";
      int to_match_nb_blocks = 10;
      for (int i = 0; i < to_match_nb_blocks; i++) BBs += "BBBBBBBBBBBBBBBB";
      string last(1, (char)X);
      string to_encrypt = block0 + BBs + block2 + last;
      assert(to_encrypt.length() == 12 + 10 * 16 + 16);

      // Encrypt, ensuring we encrypt with ECB.
      oracle.encryption_oracle((byte*)to_encrypt.c_str(), to_encrypt.length());

      while (!isAES128_ECB(oracle.getCiphertext()->data_ptr,
                           oracle.getCiphertext()->l)) {
        oracle.encryption_oracle((byte*)to_encrypt.c_str(),
                                 to_encrypt.length());
      }

      // Save the encrypted text, this is our target for matches.
      bytearray_t to_match;
      to_match.l = oracle.getCiphertext()->l;
      to_match.data_ptr = new byte[to_match.l];
      memcpy(to_match.data_ptr, oracle.getCiphertext()->data_ptr, to_match.l);

      const byte* unknown_block = &target.data_ptr[unknown_char_pos];
      const byte* block_to_match =
          &to_match.data_ptr[(to_match_nb_blocks + 1) * 16];

      if (memcmp(unknown_block, block_to_match, 16) == 0) {
        char_found = true;
        string x(1, (char)X);
        cout << x << endl;
        decrypted += x;
        remainging_len--;
      }
    }
  }
  cout << decrypted << endl;
}

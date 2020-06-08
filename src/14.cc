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
#define RANDOM_PREFIX_MAX_LEN 16

using namespace std;

void attackRandomPrefix(string unknown_string_cpp_s) {
  /** Attack on fixed size offset.
   *
   * In the following section with break with the oracle the encrypted input,
   * and recover the unknown_string
   *************************************************************************/

  // 0. Set the oracle with a random prefix with random length.
  int random_prefix_len = rand() % RANDOM_PREFIX_MAX_LEN;
  string random_prefix = "";

  // Create random bytes
  for (int i = 0; i < random_prefix_len; i++) {
    byte b = rand() % 256;
    string bs(1, b);
    random_prefix += bs;
  }

  // Debug
  cout << "random_prefix_len: " << random_prefix_len << endl;

  Oracle oracle;
  oracle.setOffsetType(FIXED);
  oracle.setOffset(random_prefix.c_str());

  oracle.debug_printOffset();

  // 1. Detect the block size: when we feed the oracle with bigger strings
  int blocksize = detectBlockSize(oracle);
  cout << "Detected blocksize: " << blocksize << endl;

  // 2. Detect the encryption mode:
  bool char_found = false;
  string decrypted = "";

  int offset_len = detectOffsetLength(oracle, blocksize);
  cout << "Offset size: ";
  cout << offset_len << endl;

  // Create offset's complement:
  string block0 = "";

  int start = offset_len % blocksize;
  for (int i = start; i < blocksize; i++) {
    string b(1, 'A');
    block0 += b;
  }

  // 3. Create plaintexts like AAAAAAAAAAAAAAAX, AAAAAAAAAAAAAAAX'...
  // where X, X', etc are letters.
  string block1 = "";                 // Additional blocks to detect ECB.
  string block2 = "AAAAAAAAAAAAAAA";  // Contain the secret byte at the end.

  // Check our values are correct:
  assert(block0.length() == blocksize - offset_len);
  assert(block2.length() == 15);

  int unknown_string_len = unknown_string_cpp_s.length();
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
      // We expand the target string with several "BBBBBBBBBBBBBBBB" (blocksize
      // bytes long) to be able to recognize when ECB is used.
      string BBs = "";
      int to_match_nb_blocks = 8;
      for (int i = 0; i < to_match_nb_blocks; i++) BBs += "BBBBBBBBBBBBBBBB";
      string last(1, (char)X);
      string to_encrypt = block0 + BBs + block2 + last;
      assert(to_encrypt.length() ==
             block0.length() + (to_match_nb_blocks + 1) * blocksize);

      // Encrypt, ensuring we encrypt with ECB by repeated calls to the oracle
      // function.
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

void challenge_14() {
  /** The goal is to find target-bytes when adding a random prefix to every
   * plaintext:
   *
   * AES-128-ECB(random-prefix || attacker-controlled || target-bytes,
   * random-key)
   *
   */

  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 2" << endl;
  cout << "14. Byte-at-a-time ECB decryption (Harder)" << endl;
  cout << "------------------------------------\n" << endl;

  cout << std::boolalpha;  // Display booleans as true/false strings.
  srand(time(NULL));

  // Unknown string (base64'ed)to cipher, this is our target.
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

  attackRandomPrefix(unknown_string_cpp_s);
}

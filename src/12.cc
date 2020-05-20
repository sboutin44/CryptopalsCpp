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

void detectOffsetLength() {
  //	  // Guess the offset (which should not be known by the attacker
  // beforehand)
  ////  	byte* first_block_enc  = new byte[blocksize];
  // oracle.setOffsetType(FIXED);
  // oracle.setOffset( "XXXX" );
  // oracle.printOffset();
  //	  string bl = "AAAAAAAAAAAAAAAA";
  //	  string middle = bl + bl + bl;
  //	  oracle.clear();
  //	oracle.encryption_oracle((byte*)middle.c_str(), middle.length(), key);
  //
  //	const byte* b1 = &oracle.getEntryData(oracle.size()-1)[16];
  //	const byte* b2 = &oracle.getEntryData(oracle.size()-1)[32];
  //	int is_eq = memcmp(b1,b2,16);
  ////	while(is_eq != 0) {
  //		for (int i=0;i<13;i++) {
  //		oracle.encryption_oracle((byte*)middle.c_str(), middle.length(),
  // key); 		string prefix(1, 'B'); 		middle = prefix +
  // middle; cout << middle << endl; 		new_len =
  // oracle.getEntryDataLen(oracle.size() - 1);
  //}
}

int detectBlockSize(Oracle& oracle) {
  // 1. Detect the block size: when we feed the oracle with bigger strings
  string test_string = "A";
  oracle.encryption_oracle((byte*)test_string.c_str(), test_string.length());
  int last_entry_pos = oracle.size();
  int previous_len = oracle.getEntryDataLen(last_entry_pos - 1);
  int new_len = previous_len;

  while (previous_len == new_len) {
    // Add 'A' at the end
    string suffix(1, 'A');
    test_string = test_string + suffix;
    int l_input = test_string.length();

    oracle.encryption_oracle((byte*)test_string.c_str(), l_input);
    new_len = oracle.getEntryDataLen(oracle.size() - 1);
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

  const char* my_string =
      "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

  const char* unknown_string_b64 =
      "Um9sbGluJyBpbiBteSA1LjAKV2l0aCBteSByYWctdG9wIGRvd24gc28gbXkg"
      "aGFpciBjYW4gYmxvdwpUaGUgZ2lybGllcyBvbiBzdGFuZGJ5IHdhdmluZyBq"
      "dXN0IHRvIHNheSBoaQpEaWQgeW91IHN0b3A/IE5vLCBJIGp1c3QgZHJvdmUg"
      "YnkK";

  // Base64 decode
  uint64_t size_encoded = strlen(unknown_string_b64);
  uint64_t unknown_string_len =
      getDecodedTextSize((byte*)unknown_string_b64, size_encoded);
  byte* unknown_string = new byte[unknown_string_len];
  base64Decode((byte*)unknown_string_b64, size_encoded, unknown_string);

  // Bricolage to concatenate 2 strings
  string s1((char*)my_string);
  char* unknown_string_c_str = new char[unknown_string_len];
  memcpy(unknown_string_c_str, unknown_string, unknown_string_len);
  unknown_string_c_str[unknown_string_len] = '\0';
  string unknown_string_cpp_s(unknown_string_c_str);
  string s2(unknown_string_c_str);

  /**************************************************************************
   * In the following section with break with the oracle the encrypted input,
   * and recover the unknown_string
   *************************************************************************/

  // 0. Set the oracle type, should be removed when every works at the end.
  Oracle oracle;
  oracle.setOffsetType(FIXED);
  oracle.setOffset("XXXX");
  oracle.printOffset();

  Vector dict;
  bytearray_t entry;

  // 1. Detect the block size: when we feed the oracle with bigger strings
  int blocksize = detectBlockSize(oracle);
  cout << "Detected blocksize: " << blocksize << endl;

  // 2. Detect the encryption mode:
  bool char_found = false;
  string decrypted = "";

  // 3. Create plaintexts like AAAAAAAAAAAAAAAX, AAAAAAAAAAAAAAAX'...
  // where X, X', etc are letters in the
  string block0 =
      "AAAAAAAAAAAA";  // Compensate the offset with meaningless 'A's.
  string block1 = "";  // Additional blocks to detect ECB.
  string block2 = "AAAAAAAAAAAAAAA";  // Contain the secret byte at the end.

  int offset_len =
      4;  // Should be discovered with the function detectOffsetLength.
  assert(block0.length() == blocksize - offset_len);
  //  assert(block1.length() == 16);
  assert(block2.length() == 15);

  int remainging_len = unknown_string_len;

//  while (remainging_len > 0) {
    // Create a 16*coef bytes long string, long enough to detect ECB mode:
    int coef = 100;
    for (int i = 0; i < (coef * 16 + 15); i++) {
      string c(1, 'A');
      block1 += c;
    }

    string plaintext = block0 + block1 + unknown_string_cpp_s;
    oracle.clear();

    // Replace last bytes by the discovered onces, if any.
    int count = decrypted.length();
    for (int i = 0; i < count; i++) {
      block1.pop_back();
    }
    block1 += decrypted;

    // Encrypt, ensuring we encrypt with ECB.
    oracle.encryption_oracle((byte*)plaintext.c_str(), plaintext.length());
    int pos = 0;
    while (
        !isAES128_ECB(oracle.getEntryData(pos), oracle.getEntryDataLen(pos))) {
      oracle.removeEntry(pos);  // Remove the last entry since CBC.
      oracle.encryption_oracle((byte*)plaintext.c_str(), plaintext.length());
      pos = oracle.size() - 1;
    }

    int unknown_char_pos = 16 + coef * 16;

    // Encrypt all possible AAAAAAAAAAAAAAAx
    for (int X = 0; X <= 0xFF; X++) {
    	string AAs = "AAAAAAAAAAAAAAAA";
    	string BBs = "";
    	for (int i=0;i<10;i++)
    		BBs += "BBBBBBBBBBBBBBBB";
//    		AAs += "AAAAAAAAAAAAAAAA";
    	string last(1, (char)X);
    	string to_encrypt = block0 + BBs + block2 + last;
    	assert(to_encrypt.length() == 12+10*16+16);
      // Encrypt, ensuring we encrypt with ECB.
      oracle.encryption_oracle((byte*)to_encrypt.c_str(), to_encrypt.length());
      int pos = oracle.size()-1;
      while (
          !isAES128_ECB(oracle.getEntryData(pos), oracle.getEntryDataLen(pos))) {
        oracle.removeEntry(pos);  // Remove the last entry since CBC.
        oracle.encryption_oracle((byte*)to_encrypt.c_str(), to_encrypt.length());
        pos = oracle.size() - 1;
      }

      // Save the output to our dictionary.
      dict.push_back(
          oracle.getEntryData(oracle.size() - 1),
          oracle.getEntryDataLen(oracle.size() - 1));  // Copies the array.
      const byte* unknown_string_block =
          &oracle.getEntryData(0)[unknown_char_pos];
      const byte* my_block = &oracle.getEntryData(oracle.size() - 1)[11*16];

//      cout << oracle.size() << endl;
      if (memcmp(unknown_string_block, my_block, 16) == 0) {
        char_found = true;
        cout << "That's a match !" << endl;
        string x(1, (char)X);
        decrypted += x;
        remainging_len--;
      } else {

      }
      // Shift the string from 1 char to the left;
    }
//  }
  cout << decrypted << endl;
}

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

void getOffset() {
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

  srand(time(NULL));

  //  int l_plaintext;
  //  const char* filename = "resources/united_states.txt";
  //  uint8_t* my_string = (uint8_t*)read_text_file(filename, &l_plaintext);

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

  // TODO: add again
    string s3 = s1 + s2;
//  string s3(s1);
  const char* input = s3.c_str();
  int l_input = strlen(input);
  Oracle oracle;

  // Generate a key
  byte* key = new byte[16];
  randomAES128key(key);

  // Pad then Encrypt
  int len = l_input;
  int blocksize = 16;
  int pad_len = blocksize - len % blocksize;
  int len_out = len + pad_len;
  byte* buffer = new byte[len_out];
  byte* ciphertext_ECB = new byte[len_out];

  PKCS7_padding((byte*)input, len, buffer, blocksize);
  AES128_ECB_encrypt(buffer, key, len_out, ciphertext_ECB);

  /**************************************************************************
   * In the following section with break with the oracle the encrypted input,
   * and recover the unknown_string
   *************************************************************************/

  // 0. Set the oracle type, should be removed when every works at the end.
  oracle.setOffsetType(FIXED);
  oracle.setOffset("XXXX");
  oracle.printOffset();

  // 1. Detect the block size: when we feed the oracle with bigger strings
  blocksize = detectBlockSize(oracle);
  cout << "Detected blocksize: " << blocksize << endl;

  // 2. Detect the encryption mode:
  cout << std::boolalpha;  // Display booleans as true/false strings.
  cout << "isAES128_CBC: " << isAES128_CBC(ciphertext_ECB, len_out) << endl;
  cout << "isAES128_ECB: " << isAES128_ECB(ciphertext_ECB, len_out) << endl;

  // 3. Create plaintexts like AAAAAAAAAAAAAAAX, AAAAAAAAAAAAAAAX'...
  // where X, X', etc are letters in the
  string block0 = "AAAAAAAAAAAA";  // Populate the offset with meaningless 'A's.
  string block1 =
      "AAAAAAAAAAAAAAA";  // Contain the secret byte at the end.
  string plaintext = block0 + block1 + unknown_string_cpp_s;
  oracle.clear();
  string decrypted = "";

  // Encrypt AAAAA...A || unknown-string-byte || unknown-string, ensuring we encrypt with ECB.
  oracle.encryption_oracle((byte*)plaintext.c_str(), plaintext.length());
  int last_elem_pos = 0;
  const byte* unknown_string_enc = oracle.getEntryData(last_elem_pos);
  while (!isAES128_ECB(unknown_string_enc,oracle.getEntryDataLen(last_elem_pos))) {
	  oracle.encryption_oracle((byte*)plaintext.c_str(), plaintext.length());
	  last_elem_pos = oracle.size()-1;
	  unknown_string_enc = oracle.getEntryData(last_elem_pos);
  }

  cout << "Display the encrypted AAAAA..AAAX: (look the 2nd block)";
  oracle.printEntries();

  // Encrypt all AAAAA.....AX to later compare the 2nd block to
  for (int X = 0; X <= 0xFF; X++) {
    string last(1, (char)X);
    string to_encrypt = block0 + block1 + last;
    oracle.encryption_oracle((byte*)to_encrypt.c_str(), to_encrypt.length());
    const byte* unknown_string_block = &oracle.getEntryData(0)[16];
    const byte* my_block = &oracle.getEntryData(oracle.size() - 1)[16];

    //    cout << oracle.size() << endl;
    if (memcmp(unknown_string_block, my_block, 16) == 0) {
      cout << "That's a match !" << endl;
      string x(1, (char)X);
      decrypted += x;
    };
  }
  cout << decrypted << endl;

}

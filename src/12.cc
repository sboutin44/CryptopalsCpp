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

void challenge_12() {
  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 2" << endl;
  cout << "12. Byte-at-a-time ECB decryption (Simple)" << endl;
  cout << "------------------------------------\n" << endl;

  srand(time(NULL));

  const char* my_string =
      "You can go in thYou can go in thYou can go in thYou can go in thYou can "
      "go in thYou can go in thYou can go in thYou can go in thYou can go in "
      "thYou can go in thYou can go in thYou can go in thYou can go in thYou "
      "can go in thYou can go in thYou can go in thYou can go in thYou can go "
      "in thYou can go in thYou can go in thYou can go in thYou can go in th";

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
  string s1(my_string);
  char* unknown_string_c_str = new char[unknown_string_len];
  memcpy(unknown_string_c_str, unknown_string, unknown_string_len);
  unknown_string_c_str[unknown_string_len] = '\0';
  string s2(unknown_string_c_str);
  string s3 = s1 + s2;

  const char* input = s3.c_str();

  int l_input = strlen(input);

  Oracle oracle;
  int nbEntries = 50;

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

  for (int i = 0; i < nbEntries; i++)
    oracle.encryption_oracle((byte*)input, l_input);
}

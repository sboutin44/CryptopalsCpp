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

void repeatedKeyXor(const char* input, const char* key, char* output) {
  int inputSize = strlen(input);
  int keySize = strlen(key);

  for (int i = 0; i < inputSize; i++) {
    output[i] = input[i] ^ key[i % keySize];
  }
}

void challenge_5() {
  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 1" << endl;
  cout << "5. Implement repeating-key XOR" << endl;
  cout << "------------------------------------\n" << endl;

  const char* expected_str =
      "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765"
      "272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27"
      "282f";
  uint8_t* expected = new uint8_t[strlen(expected_str) / 2];
  hexDecode(expected_str, expected);

  const char* a =
      "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a "
      "cymbal";
  const char* key = "ICE";
  char* output;

  output = new char[strlen(a)];
  repeatedKeyXor(a, key, output);
  printf("\n");
  for (int i = 0; i < (int)strlen(a); i++) printf("%02x", output[i]);
  printf("\n");
  for (int i = 0; i < (int)strlen(a); i++) printf("%02x", expected[i]);
  printf("\n");

  assert(memcmp((uint8_t*)output, expected, strlen(expected_str) / 2) == 0);

  delete[] output;
}

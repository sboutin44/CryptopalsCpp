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

#include <cassert>
#include <cstring>

#include "block_ciphers.h"

using namespace std;

void testAES128_CBC_allocate(byte* input, int len) {
  //	AES128_ECB_allocate()
}

void testPKCS7_padding() {
  int blocksize = 16;

  // 1 block Tests values
  int len1 = AES128_BLOCKSIZE - 6;  // 16-6
  const byte plaintext1[AES128_BLOCKSIZE - 6] = {0x31, 0x32, 0x33, 0x34, 0x35,
                                                 0x36, 0x37, 0x38, 0x39, 0x30};
  const byte manually_padded_plaintext1[16] = {
      0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
      0x39, 0x30, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06};

  int len2 = AES128_BLOCKSIZE - 5;
  const byte plaintext2[AES128_BLOCKSIZE - 5] = {
      0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30, 0x22};
  const byte manually_padded_plaintext2[16] = {
      0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
      0x39, 0x30, 0x22, 0x05, 0x05, 0x05, 0x05, 0x05};

  int len3 = AES128_BLOCKSIZE - 1;
  const byte plaintext3[AES128_BLOCKSIZE - 1] = {0x31, 0x32, 0x33, 0x34, 0x35,
                                                 0x36, 0x37, 0x38, 0x39, 0x30,
                                                 0x22, 0x22, 0x22, 0x22, 0x22};
  const byte manually_padded_plaintext3[16] = {
      0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
      0x39, 0x30, 0x22, 0x22, 0x22, 0x22, 0x22, 0x01};

  // Text 1
  byte* buffer1 = AES128_CBC_allocate((byte*)plaintext1, len1);
  PKCS7_padding((byte*)plaintext1, len1, buffer1, blocksize);
  assert(memcmp(buffer1, manually_padded_plaintext1, blocksize) == 0);

  // Text 2
  byte* buffer2 = AES128_CBC_allocate((byte*)plaintext2, len2);
  PKCS7_padding((byte*)plaintext2, len2, buffer2, blocksize);
  assert(memcmp(buffer2, manually_padded_plaintext2, blocksize) == 0);

  // Text 3
  byte* buffer3 = AES128_CBC_allocate((byte*)plaintext3, len3);
  PKCS7_padding((byte*)plaintext3, len3, buffer3, blocksize);
  assert(memcmp(buffer3, manually_padded_plaintext3, blocksize) == 0);

  cout << "testPKCS7_padding \tpassed" << endl;
}

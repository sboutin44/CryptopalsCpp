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

void testDetectBlockSize() {
  int AES128_blocksize = 16;

  Oracle oracle;
  oracle.setOffsetType(FIXED);
  oracle.setOffset("XXXX");

  int blocksize = detectBlockSize(oracle);
  assert(blocksize == AES128_blocksize);

  cout << "testDetectBlockSize \tpassed" << endl;
}

void testDetectOffsetLength() {
  Oracle oracle;
  oracle.setOffsetType(FIXED);
  int blocksize = 16;

  for (int i = 1; i < 10; i++) {
    // Create a string of i bytes.
	  string offset = "";
	  for (int j = 0; j< i; j++) offset += "X";

    cout << offset << endl;
    //  oracle.setOffset("XXXX");
    oracle.setOffset(offset.c_str());

    oracle.debug_printOffset();

    int offset_len = detectOffsetLength(oracle, blocksize);
    assert(i == offset_len);
  }
}

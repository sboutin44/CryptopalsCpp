// Copyright © 2020 Sebastien BOUTIN
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// Except as contained in this notice, the name(s) of the above copyright
// holders shall not be used in advertising or otherwise to promote the sale,
// use or other dealings in this Software without prior written authorization.

#include "lib.h"
using namespace std;

uint8_t* myXOR(uint8_t* a, uint8_t* b, int size) {
  uint8_t* c = new uint8_t[size];

  for (int i = 0; i < size; i++) c[i] = a[i] ^ b[i];

  return c;
}

void challenge_2() {
  cout << "\n============================" << endl;
  cout << "Fixed XOR" << endl;
  uint8_t a[] = {0x1c, 0x01, 0x11, 0x00, 0x1f, 0x01, 0x01, 0x00, 0x06,
                 0x1a, 0x02, 0x4b, 0x53, 0x53, 0x50, 0x09, 0x18, 0x1c};
  uint8_t b[] = {0x68, 0x69, 0x74, 0x20, 0x74, 0x68, 0x65, 0x20, 0x62,
                 0x75, 0x6c, 0x6c, 0x27, 0x73, 0x20, 0x65, 0x79, 0x65};

  cout << "a: " << a << endl;
  cout << "b: " << b << endl;

  uint8_t* c = myXOR(a, b, sizeof(a));
  cout << "c: " << c << endl;

  //    uint8_t* d = myXOR( c, b, sizeof(c));
  //    cout << "d: " << d << endl;
  //    assert(memcmp(a,d,sizeof(a)) == 0);
}

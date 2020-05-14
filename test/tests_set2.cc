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

void testGuessEncryptionMode() {
  srand(time(NULL));

  int nbEntries = 50;
  byte* enc_mode[nbEntries];

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

  // Guess the encryption mode for each entries, and verify them to result
  // computed during the creation of the ciphers.
  for (int i = 0; i < nbEntries; i++) {
    byte* entry = new byte[oracle.getEntryDataLen(i)];
    oracle.getEntryData(i, entry);

    bool real_mode = oracle.enc_mode_order[i];
    bool guessed_mode = guessEncryptionMode(entry, oracle.getEntryDataLen(i));
    assert(real_mode == guessed_mode);
  }
  cout << "testGuessEncryptionMode passed" << endl;
}

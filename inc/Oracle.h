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

#ifndef CRYPTOPALS_INC_ORACLE_H_
#define CRYPTOPALS_INC_ORACLE_H_

#include "types.h"
#include "lib.h"

/*-------------------------- Oracle ----------------------*/

typedef struct bytearray_t {
  int l;
  byte* data_ptr;
} bytearray_t;

enum ENCRYPTION_MODE { ECB, CBC };
enum OFFSET_TYPE { NO_OFFSET, RANDOM, FIXED };

class Oracle {
 private:
  bytearray_t ciphertext;
  std::vector<bytearray_t> entries;
  OFFSET_TYPE offsetType;
  bytearray_t offset;
  byte* key;  // AES128 - 16 bytes long

 public:
  // Constructor
  Oracle();

  // Oracle interface
  void encryption_oracle(byte* input, int l_input);
  void encryption_oracle(byte* input, int l_input, byte* key);
  int getEntryDataLen(int pos);
  const byte* getEntryData(int pos);
  void getEntryData(int pos, byte* dst);
  const bytearray_t* getCiphertext();

  // Oracle customization
  void setOffsetType(OFFSET_TYPE ot);
  void setOffset(const char* s);
  void setKey(byte* key, int len);

  // For debug purpose
  const byte* getKey();
  void addEntry(bytearray_t input);
  void debug_removeEntry(int pos);
  void insertAtBegin(byte* arr, int l);
  void clear();
  std::vector<ENCRYPTION_MODE> debug_enc_mode;
  int debug_size();
  std::vector<bytearray_t> getEntries();
  void debug_printEntries();
  void debug_printEntry(int);
  void debug_printOffset();
  void debug_printRealMode(int pos);
};

#endif  // CRYPTOPALS_INC_ORACLE_H_

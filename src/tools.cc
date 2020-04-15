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

char* read_text_file(const char* filename, int* length) {
  /** Return a text read from a file as well as its length.
   *
   * No prior allocation is needed since we don't know the text size before
   * reading the file.
   *
   * @param  filename A text file.
   * @return text     An allocated char array with the text.
   * @return length   The length of the read text.
   */

  ifstream file;
  char* out;

  try {
    file.open(filename);

    if (file.fail()) throw file.rdstate();

    // get length of file:
    file.seekg(0, file.end);
    *length = file.tellg();
    file.seekg(0, file.beg);

    out = (char*)malloc(sizeof(char) * (*length));
    assert(out != NULL);

    file.read(out, *length);
  } catch (ios::iostate filestate) {
    if (filestate == ios::failbit) {
      cout << "failbit" << endl;
    }

    if (filestate == ios::badbit) {
      cout << "badbit" << endl;
    }
  }
  return out;
}

char* read_text_file(const char* filename) {
  /** Read a text file and discard the text length. */
  int length;
  return read_text_file(filename, &length);
}

int occurence_byte(uint8_t* s, uint8_t myChar, int length) {
  /** Occurence of a character in a random byte string.  */

  int occ = 0;
  uint8_t current = s[0];

  int i = 0;
  while (i != length) {
    if (current == myChar) occ++;
    current = s[i + 1];
    i++;
  }
  return occ;
}

int occurence(const char* s, char myChar) {
  int occ = 0;
  char current = tolower(s[0]);

  int i = 0;
  while (current != '\0') {
    if (current == myChar) occ++;
    current = tolower(s[i + 1]);
    i++;
  }
  return occ;
}

int occurence(uint8_t* s, char myChar, int length) {
  /** Occurrence of a character in a random byte string.  */

  int occ = 0;
  char current = tolower(s[0]);

  int i = 0;
  while (i != length) {
    if (current == myChar) occ++;
    current = tolower(s[i + 1]);
    i++;
  }
  return occ;
}

float frequency(const char* s, char c) {
  if (occurence(s, c) == 0) {
    return 0;
  } else {
    return ((float)occurence(s, c) / (float)strlen(s));
  }
}

float frequency(uint8_t* s, char c, int length) {
  /** Frequency (0<f<100) of a character in a random byte string */

  if (occurence(s, c, length) == 0) {
    return 0;
  } else {
    return ((float)occurence(s, c, length) / (float)length);
  }
}
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

uint8_t* read_base64_file(const char* filename, int* length) {
  ifstream file;
  uint8_t* out;

  try {
    file.open(filename);

    if (file.fail()) throw file.rdstate();

    // get length of file:
    file.seekg(0, file.end);
    *length = file.tellg();
    file.seekg(0, file.beg);

    // Count lines
    int f = 0;
    uint64_t sizeDecoded = 0;
    uint64_t sizeLineDecoded = 0;

    for (std::string line; std::getline(file, line);) {
      sizeLineDecoded =
          getDecodedTextSize((uint8_t*)line.c_str(), strlen(line.c_str()));
      // cout << sizeLineDecoded << endl;
      sizeDecoded += sizeLineDecoded;
      // getDecodedTextSize((uint8_t*)line.c_str(), strlen(line.c_str()));
    }
    file.seekg(0, file.beg);
    file.close();
    file.open(filename);

    *length = sizeDecoded;
    out = new uint8_t[sizeDecoded];
    assert(out != NULL);

    // Read the file line by line, and remove line endings.
    int pos = 0;  // position in out
    for (std::string line; std::getline(file, line);) {
      sizeLineDecoded =
          getDecodedTextSize((uint8_t*)line.c_str(), strlen(line.c_str()));

      int line_len = strlen(line.c_str());
      // memcpy(&out[pos], line.c_str(), line_len);
      base64Decode((uint8_t*)line.c_str(), line_len, &out[pos]);

      // cout << line << endl;
      // for (int i = 0; i < strlen(line.c_str()); i++)
      //   printf("%s", &out[pos + i]);
      // cout << endl;

      pos += sizeLineDecoded;
    }
    cout << "pos: " << pos << endl;

  } catch (ios::iostate filestate) {
    if (filestate == ios::failbit) {
      cerr << "failbit" << endl;
    }

    if (filestate == ios::badbit) {
      cerr << "badbit" << endl;
    }
    cerr << "Failed to open file '" << filename << "'" << endl;
    exit(EXIT_FAILURE);
  }
  return out;
}

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

    // // Read the file line by line, and remove line endings.
    // int pos = 0;  // position in out
    // for (std::string line; std::getline(file, line);) {
    //   int line_len = strlen(line.c_str());
    //   memcpy(&out[pos], line.c_str(), line_len);
    //   pos += line_len;
    // }

    file.read(out, *length);
  } catch (ios::iostate filestate) {
    if (filestate == ios::failbit) {
      cerr << "failbit" << endl;
    }

    if (filestate == ios::badbit) {
      cerr << "badbit" << endl;
    }
    cerr << "Failed to open file '" << filename << "'" << endl;
    exit(EXIT_FAILURE);
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
    current = s[i];
    if (current == myChar) occ++;
    i++;
  }
  return occ;
}

int occurence(const char* s, char myChar) {
  int occ = 0;
  char current = tolower(s[0]);

  int i = 0;
  while (current != '\0') {
    current = tolower(s[i]);
    if (current == myChar) occ++;
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
    current = tolower(s[i]);
    if (current == myChar) occ++;
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

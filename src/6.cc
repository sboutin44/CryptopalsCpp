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

void display_map() {}

void insertion_sort(float arr[], float n) {
  int i, j;
  float key;
  for (i = 1; i < n; i++) {
    key = arr[i];
    j = i - 1;

    /* Move elements of arr[0..i-1], that are
    greater than key, to one position ahead
    of their current position */
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j = j - 1;
    }
    arr[j + 1] = key;
  }
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

int hammingDistance(uint8_t* a, uint8_t* b, int n) {
  uint8_t byte;
  int distance = 0;

  for (int i = 0; i < n; i++) {
    byte = a[i] ^ b[i];

    int j = 0;
    while (j < 8) {
      distance += (byte >> j) & 1;
      j++;
    }
  }
  return distance;
}

void TestHammingDistance() {
  string a = "this is a test";
  string b = "wokka wokka!!!";
  int n = strlen(a.c_str());
  cout << hammingDistance((uint8_t*)a.c_str(), (uint8_t*)b.c_str(), n) << endl;
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
  /** Occurence of a character in a random byte string.  */

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

void plot_frequencies(uint8_t* candidate, int length) {
  /** Plot frequencies for the first 5 letters. */
  int f1 = 2 * 100 * frequency(candidate, 'e', length);
  int f2 = 2 * 100 * frequency(candidate, 't', length);
  int f3 = 2 * 100 * frequency(candidate, 'a', length);
  int f4 = 2 * 100 * frequency(candidate, 'o', length);
  int f5 = 2 * 100 * frequency(candidate, 'i', length);
  int f6 = 2 * 100 * frequency(candidate, 'n', length);

  cout << "e ";
  for (int i = 0; i < f1; i++) cout << "-";
  cout << endl;

  cout << "t ";
  for (int i = 0; i < f2; i++) cout << "-";
  cout << endl;

  cout << "a ";
  for (int i = 0; i < f3; i++) cout << "-";
  cout << endl;

  cout << "o ";
  for (int i = 0; i < f4; i++) cout << "-";
  cout << endl;

  cout << "i ";
  for (int i = 0; i < f5; i++) cout << "-";
  cout << endl;

  cout << "n ";
  for (int i = 0; i < f6; i++) cout << "-";
  cout << endl;
}

void histogram(const char* text, int len) {
  int f1 = 100 * frequency(text, 'e');
  int f2 = 100 * frequency(text, 't');
  int f3 = 100 * frequency(text, 'a');
  int f4 = 100 * frequency(text, 'o');
  int f5 = 100 * frequency(text, 'i');
  int f6 = 100 * frequency(text, 'n');
  int f7 = 100 * frequency(text, 's');
  int f8 = 100 * frequency(text, 'r');
  int f9 = 100 * frequency(text, 'h');
  int f10 = 100 * frequency(text, 'd');
  int f11 = 100 * frequency(text, 'l');
  int f12 = 100 * frequency(text, 'u');
  int f13 = 100 * frequency(text, 'c');
  int ratioNonPrintables = 100 * ratioNonPrintChars((uint8_t*)text, len);

  // Frequencies of char that are not so present in an english sentence
  int s = 0;
  s += 100 * frequency(text, '@');
  s += 100 * frequency(text, '$');
  s += 100 * frequency(text, '%');
  s += 100 * frequency(text, '^');
  s += 100 * frequency(text, '&');
  s += 100 * frequency(text, '#');
  s += 100 * frequency(text, '*');
  s += 100 * frequency(text, '&');
  s += 100 * frequency(text, '{');
  s += 100 * frequency(text, '}');
  s += 100 * frequency(text, '|');
  //  s += 100 * frequency(text, '\\');

  cout << endl;

  int hist_heigth = 15;
  int i = hist_heigth;
  while (i > 0) {
    // Print a single line
    printf(" | ");
    if (f1 >= i)
      printf(" * ");
    else
      printf("   ");
    if (f2 >= i)
      printf(" * ");
    else
      printf("   ");
    if (f3 >= i)
      printf(" * ");
    else
      printf("   ");
    if (f4 >= i)
      printf(" * ");
    else
      printf("   ");
    if (f5 >= i)
      printf(" * ");
    else
      printf("   ");
    if (f6 >= i)
      printf(" * ");
    else
      printf("   ");
    if (f7 >= i)
      printf(" * ");
    else
      printf("   ");
    if (f8 >= i)
      printf(" * ");
    else
      printf("   ");
    if (f9 >= i)
      printf(" * ");
    else
      printf("   ");
    if (f10 >= i)
      printf(" * ");
    else
      printf("   ");
    if (f11 >= i)
      printf(" * ");
    else
      printf("   ");
    if (f12 >= i)
      printf(" * ");
    else
      printf("   ");
    if (f13 >= i)
      printf(" * ");
    else
      printf("   ");

    // Separation with letters
    printf("    ");

    if (s >= i)
      printf(" * ");
    else
      printf("    ");

    printf("   ");

    if (ratioNonPrintables >= i)
      printf(" * ");
    else
      printf("   ");

    cout << endl;
    i--;
  }
  printf("   ---------------------------------------   -------------\n");
  printf("    e  t  a  o  i  n  s  r  h  d  l  u  c    sym  non-print\n");
}

void plot_frequencies(const char* text) {
  /** Plot frequencies for the first 5 letters. */
  int f1 = 2 * 100 * frequency(text, 'e');
  int f2 = 2 * 100 * frequency(text, 't');
  int f3 = 2 * 100 * frequency(text, 'a');
  int f4 = 2 * 100 * frequency(text, 'o');
  int f5 = 2 * 100 * frequency(text, 'i');
  int f6 = 2 * 100 * frequency(text, 'n');

  cout << endl;

  cout << "e ";
  for (int i = 0; i < f1; i++) cout << "*";
  cout << endl;

  cout << "t ";
  for (int i = 0; i < f2; i++) cout << "*";
  cout << endl;

  cout << "a ";
  for (int i = 0; i < f3; i++) cout << "*";
  cout << endl;

  cout << "o ";
  for (int i = 0; i < f4; i++) cout << "*";
  cout << endl;

  cout << "i ";
  for (int i = 0; i < f5; i++) cout << "*";
  cout << endl;

  cout << "n ";
  for (int i = 0; i < f6; i++) cout << "*";
  cout << endl;
}

void challenge_6() {
  /** 6. Break repeating-key XOR
   *
   * Here I follow the guidelines provided in the challenge.
   */

  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 1" << endl;
  cout << "6. Break repeating-key XOR" << endl;
  cout << "------------------------------------\n" << endl;

  // TestHammingDistance();
  int l;  // lenght of the cipher.
  char* base64ed_encrypted_text = read_text_file("resources/6.txt", &l);
  uint8_t* encrypted_text = base64Decode(base64ed_encrypted_text, l);

  // 1)
  map<float, int> m;
  int d;
  float n;
  int keylen_start = 2;
  int keylen_end = 40;
  int nb_keys = keylen_end - keylen_start + 1;
  int pos = 0;  // To browse norm_distances
  float* norm_distances = new float[nb_keys];
  int KEYSIZE;

  for (KEYSIZE = 2; KEYSIZE <= keylen_end; KEYSIZE++) {
    d = hammingDistance(encrypted_text, encrypted_text + KEYSIZE, KEYSIZE);
    n = (float)d / KEYSIZE;
    // n = (float)d / (float)KEYSIZE;
    m[n] = KEYSIZE;             // Map normalised_KEYSIZE -> KEYSIZE
    norm_distances[pos++] = n;  // To sort the normalised KEYSIZE.
  }

  // 4
  insertion_sort(norm_distances, nb_keys);

  // 5
  // We break the ciphertext into several blocks.
  // We define the variable 'int** blocks' as follow:
  //
  //  |                                l                           |
  //  ==============================================================
  //   [c].............[c'].............[c"]
  //  ==============================================================
  //  |               |               |               | ...        |
  //       KEYSIZE         KEYSIZE         KEYSIZE
  //
  // Then we define block[0] = [c][c'][c"]... is of length p = l / KEYSIZE.
  // Where c,c' and c" are bytes.
  // We have thus KEYSIZE of these blocks, each of length p.

  // // Display normalised key sizes:
  // for (int i = 0; i < nb_keys; i++) {
  //   cout << "norm_distances[i]: " << norm_distances[i] << endl;
  //   cout << m[norm_distances[i]] << endl;
  // }

  // remettre
  KEYSIZE = 5;

  int p = l / KEYSIZE;  // p blocks
  // uint8_t** blocks = (uint8_t**)malloc(sizeof(uint8_t*) * p);
  uint8_t** blocks = (uint8_t**)malloc(sizeof(uint8_t*) * KEYSIZE);
  assert(blocks != NULL);
  cout << "p: " << p << endl;

  // Create the blocks of length p each.
  for (int block_num = 0; block_num < KEYSIZE; block_num++) {
    blocks[block_num] = (uint8_t*)malloc(sizeof(uint8_t) * p);
    assert(blocks[block_num] != NULL);

    // Fill the block with bytes c,c', c", etc...
    for (int i = 0; i < p; i++)
      blocks[block_num][i] = encrypted_text[block_num + KEYSIZE * i];
  }

  // Histograms:
  // // for (int j = 0; j < p; j++) printf("%c", blocks[j]);
  // long int var = 0;
  // uint8_t* repeatedkey = new uint8_t[KEYSIZE];
  // char* decrypted = new uint8_t[l];
  //
  //  // extend the key
  //  repeatedkey[0] = 67; // 38 49 64  81 85
  //  repeatedkey[1] = key_2;
  //  repeatedkey[2] = key_3;
  //  repeatedkey[3] = key_4;
  //  repeatedkey[4] = 0; // dummy
  //
  //  repeatedKeyXor((char*)encrypted_text, (char*)repeatedkey, decrypted);

  singlebyteXORattackWithFrequencyScore(blocks[1], p, 1.);

  // Try to decrypt:
  // Hypothesis:
  //
  uint8_t keyByte1 = 67;

  // uint8_t* repeatedkey = new uint8_t[KEYSIZE];
  //
  // //memset(repeatedkey, (uint8_t)singleByteKey, KEYSIZE);
  // char* output = new char[l];
  // repeatedKeyXor((char*)encrypted_text, (char*)repeatedkey, output);
  //
  // // Display decrypted text:
  // putchar('\n');
  // for (int j = 0; j < l; j++) printf("%c", output[j]);

  // Memory cleaning
  // for (int block_num = 0; block_num < p; block_num++) {
  //   free(blocks[block_num]);
  // }
  // free(blocks);

  // test zone
}

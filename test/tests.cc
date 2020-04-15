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

void testHammingDistance() {
  const char* a = "this is a test";
  const char* b = "wokka wokka!!!";

  const char* c = "this is a testwokka wokka!!!";

  int len_a = strlen(a);

  // Basic test
  int d1 = hammingDistance((uint8_t*)a, (uint8_t*)b, len_a);

  // Checks that is works within the same byte string.
  int d2 = hammingDistance((uint8_t*)c, (uint8_t*)&c[len_a], len_a);
  int d3 = hammingDistance((uint8_t*)c, (uint8_t*)c + len_a, len_a);

  assert(d1 == 37);
  assert(d2 == 37);
  assert(d3 == 37);

  cout << "testHammingDistance passed" << endl;
}

void testInsertionSort() {
  float a[] = {9.3, 0.1, 0.0003, 99.001, 3};
  float a_sorted[] = {0.0003, 0.1, 3, 9.3, 99.001};

  int len = sizeof(a) / sizeof(float);
  insertionSort(a, len);

  assert(memcmp((float*)a, (float*)a_sorted, len) == 0);
  cout << "testInsertionSort passed" << endl;
}

void testHistogram() {
  int N;
  const char* filename1 = "resources/aliceAdventures.txt";
  const char* english_text = read_text_file(filename1, &N);

  histogram(english_text, N);
}

void testIndexOfCoincidence() {
  // Load an english text.
  int N1, N2, N3, N4, N5, N6, N7;
  const char* filename1 = "resources/s1.txt";  // About 3700 characters
  const char* filename2 = "resources/s2.txt";
  const char* filename3 = "resources/s3.txt";
  const char* filename4 = "resources/sMax.txt";
  const char* filename5 = "resources/history.txt";
  const char* filename6 = "resources/michael.txt";
  const char* filename7 = "resources/united_states.txt";

  // float I1 = indexOfCoincidence(text1, N);
  // float I2 = indexOfCoincidence(text2, N);

  // cout << indexOfCoincidence_(text1, N1) << endl;
  // cout << indexOfCoincidence_(text2, N2) << endl;
  // cout << indexOfCoincidence_(text3, N3) << endl;

  // Index of coincidence for latin alphabet.
  cout << " Index of coincidence for latin alphabet." << endl;
  printf("%f\n",
         indexOfCoincidence_((uint8_t*)read_text_file(filename1, &N1), N1));
  printf("%f\n",
         indexOfCoincidence_((uint8_t*)read_text_file(filename2, &N2), N2));
  printf("%f\n",
         indexOfCoincidence_((uint8_t*)read_text_file(filename3, &N3), N3));
  printf("%f\n",
         indexOfCoincidence_((uint8_t*)read_text_file(filename4, &N4), N4));
  printf("%f\n",
         indexOfCoincidence_((uint8_t*)read_text_file(filename5, &N5), N5));
  printf("%f\n",
         indexOfCoincidence_((uint8_t*)read_text_file(filename6, &N6), N6));
  printf("%f\n",
         indexOfCoincidence_((uint8_t*)read_text_file(filename7, &N7), N7));

  // Index of coincidence for "ASCII" alphabet.
  cout << " Index of coincidence for ASCII alphabet." << endl;
  printf("%f\n",
         indexOfCoincidence((uint8_t*)read_text_file(filename1, &N1), N1));
  printf("%f\n",
         indexOfCoincidence((uint8_t*)read_text_file(filename2, &N2), N2));
  printf("%f\n",
         indexOfCoincidence((uint8_t*)read_text_file(filename3, &N3), N3));
  printf("%f\n",
         indexOfCoincidence((uint8_t*)read_text_file(filename4, &N4), N4));
  printf("%f\n",
         indexOfCoincidence((uint8_t*)read_text_file(filename5, &N5), N5));
  printf("%f\n",
         indexOfCoincidence((uint8_t*)read_text_file(filename6, &N6), N6));
  printf("%f\n",
         indexOfCoincidence((uint8_t*)read_text_file(filename7, &N7), N7));
}

void testFindKeyLength() {
  int l_plaintext;
  const char* filename = "resources/united_states.txt";
  uint8_t* plaintext = (uint8_t*)read_text_file(filename, &l_plaintext);

  // Cipher my own text:
  const char* key1 = "WHY";
  const char* key2 = "YOU'RE FIRED";
  const char* key3 = "What is your name?";
  const char* key4 = "terminator X: the return What is your name?";

  // Bigger keys

  int len_key5 = 1000;
  const char* key5 = new char[len_key5];
  memcpy((uint8_t*)key5, plaintext, len_key5);

  int len_key1 = strlen(key1);
  int len_key2 = strlen(key2);
  int len_key3 = strlen(key3);
  int len_key4 = strlen(key4);

  int l_ciphertext = l_plaintext;
  uint8_t* ciphertext1 = new uint8_t[l_ciphertext];
  uint8_t* ciphertext2 = new uint8_t[l_ciphertext];
  uint8_t* ciphertext3 = new uint8_t[l_ciphertext];
  uint8_t* ciphertext4 = new uint8_t[l_ciphertext];
  uint8_t* ciphertext5 = new uint8_t[l_ciphertext - 1];

  // Cipher the plaintext
  repeatedKeyXor((char*)plaintext, key1, (char*)ciphertext1);
  repeatedKeyXor((char*)plaintext, key2, (char*)ciphertext2);
  repeatedKeyXor((char*)plaintext, key3, (char*)ciphertext3);
  repeatedKeyXor((char*)plaintext, key4, (char*)ciphertext4);
  repeatedKeyXor((char*)plaintext, key5, (char*)ciphertext5);

  // Find the keys, default max key length defined in findKeyLength
  int guess_key1 = findKeyLength(ciphertext1, l_ciphertext);
  int guess_key2 = findKeyLength(ciphertext2, l_ciphertext);
  int guess_key3 = findKeyLength(ciphertext3, l_ciphertext);
  int guess_key4 = findKeyLength(ciphertext4, l_ciphertext);

  // We use a custom max key length for bigger values.
  int guess_key5 = findKeyLength(ciphertext5, l_ciphertext, len_key5 + 1);

  // Verifications.
  assert(len_key1 == guess_key1);
  assert(len_key2 == guess_key2);
  assert(len_key3 == guess_key3);
  assert(len_key4 == guess_key4);
  assert(len_key5 == guess_key5);

  cout << "\nKEYSIZE: " << len_key5 << endl;
  cout << "Guessed KEYSIZE: " << guess_key5 << endl;
}
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

#ifndef CRYPTOPALS_INC_LIB_H_
#define CRYPTOPALS_INC_LIB_H_

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

// C libraries
#include <ctype.h>

uint64_t getEncodedSize(uint8_t* input, uint64_t sizeIn);
uint64_t getDecodedTextSize(uint8_t* input, uint64_t size);
uint64_t getDecodedTextSize(uint8_t* input, uint64_t size, int* padding);
void base64Encode(uint8_t* input, uint64_t sizeIn, uint8_t* out);
void base64Decode(uint8_t* input, uint64_t size, uint8_t* output);
uint8_t* myXOR(uint8_t* a, uint8_t* b, int size);

// Defined in set_1_3_lib
void histogram(uint8_t* text, int len);
void load_dictionary(const char* filename);
int englishScore(uint8_t* sentence, int length);
int englishScore(const char* sentence, int length);
uint8_t singlebyteXORattack(uint8_t* ciphertext, int size, int thresold);
void singlebyteXORattackWithFrequencyScore(uint8_t* ciphertext, int size,
                                           float nonPrintableRatio);

// Set_1_3 Set_1_4 Set_1_5
void hexDecode(const char* input, uint8_t* out);
void singlebyteXORattack(uint8_t* ciphertext, int size);
char* read_text_file(const char* filename, int* length);
uint8_t* read_base64_file(const char* filename, int* length);
int hammingDistance(uint8_t* a, uint8_t* b, int n);
int occurence(const char* s, char myChar);
int occurence(uint8_t* s, char myChar, int length);
int occurence_byte(uint8_t* s, uint8_t myChar, int length);
float indexOfCoincidence_ASCII(uint8_t* s, int N);
float indexOfCoincidence_latin(uint8_t* s, int N);
float frequency(const char* s, char c);
float frequency(uint8_t* s, char c, int length);
float frequencyCheck(const char* s);
void repeatedKeyXor(const char* input, const char* key, char* output);
int countNonPrintableChars(uint8_t* s, int size);
float ratioNonPrintChars(uint8_t* s, int size);

// Challenge 6
void histogram(const char* text, int len);
float friedmanTest(uint8_t* s, int len);
int findKeyLength(uint8_t* ciphertext, int len, int maxKeysize);

// Tests functions:

// The challenges
void challenge_1();
void challenge_2();
void challenge_3();
void challenge_4();
void challenge_5();
void challenge_6();
void challenge_7();

// Functions in tools.h

template <typename T>
T max(T* array, int len) {
  T max = array[0];

  for (int i = 0; i < len; i++) {
    if (max < array[i]) max = array[i];
  }
  return max;
}

template <typename T>
T min(T* array, int len) {
  T min = array[0];

  for (int i = 0; i < len; i++) {
    if (min > array[i]) min = array[i];
  }
  return min;
}

template <typename T>
void insertionSort(T* arr, int n) {
  int i, j;
  T key;
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

#endif  // CRYPTOPALS_INC_LIB_H_

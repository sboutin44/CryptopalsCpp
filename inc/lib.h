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

char* base64Encode(const char* input, int size);
uint8_t* base64Decode(const char* input, int size);
uint8_t* myXOR(uint8_t* a, uint8_t* b, int size);
int test_base64();

// Defined in set_1_3_lib
void histogram(const char* text, int len);
void load_dictionary(const char* filename);
void quickEnglishChecker(uint8_t* sentence);
int englishScore(uint8_t* sentence);
int englishScore2(uint8_t* sentence, int length);
int englishScore2(const char* sentence, int length);
uint8_t singlebyteXORattack(uint8_t* ciphertext, int size, int thresold);
void singlebyteXORattackWithFrequencyScore(uint8_t* ciphertext, int size,
                                           float nonPrintableRatio);
// Set_1_3 Set_1_4 Set_1_5
void hexDecode(const char* input, uint8_t* out);
void singlebyteXORattack(uint8_t* ciphertext, int size);
void insertion_sort(float arr[], float n);
char* read_text_file(const char* filename, int* length);
int hammingDistance(uint8_t* a, uint8_t* b, int n);
int occurence(const char* s, char myChar);
int occurence(uint8_t* s, char myChar, int length);
float frequency(const char* s, char c);
float frequency(uint8_t* s, char c, int length);
float frequencyCheck(const char* s);
void plot_frequencies(const char* text);
void plot_frequencies(uint8_t* candidate, int length);
void repeatedKeyXor(const char* input, const char* key, char* output);
int countNonPrintableChars(uint8_t* s, int size);
float ratioNonPrintChars(uint8_t* s, int size);

// Tests functions:
void histogramFromPlaintext();

// The challenges
void challenge_1();
void challenge_2();
void challenge_3();
void challenge_4();
void challenge_5();
void challenge_6();
// int challenge_7();

#endif  // CRYPTOPALS_INC_LIB_H_

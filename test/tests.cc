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

void testBase64Encode() {
  // Sources of the inputs:
  // https://en.wikipedia.org/wiki/Base64

  uint8_t* res1;
  uint8_t* res2;
  uint8_t* res3;
  uint8_t* res4;
  uint8_t* res5;
  uint8_t* res6;
  uint8_t* res7;
  uint8_t* res8;
  uint8_t* res9;
  uint8_t* res10;

  const char* input_1 = "any carnal pleasure.";
  const char* input_2 = "any carnal pleasure";
  const char* input_3 = "any carnal pleasur";
  const char* input_4 = "any carnal pleasu";
  const char* input_5 = "any carnal pleas";
  const char* input_6 = "pleasure.";
  const char* input_7 = "leasure.";
  const char* input_8 = "easure.";
  const char* input_9 = "asure.";
  const char* input_10 = "sure.";

  const char* expected_output_1 = "YW55IGNhcm5hbCBwbGVhc3VyZS4=";
  const char* expected_output_2 = "YW55IGNhcm5hbCBwbGVhc3VyZQ==";
  const char* expected_output_3 = "YW55IGNhcm5hbCBwbGVhc3Vy";
  const char* expected_output_4 = "YW55IGNhcm5hbCBwbGVhc3U=";
  const char* expected_output_5 = "YW55IGNhcm5hbCBwbGVhcw==";
  const char* expected_output_6 = "cGxlYXN1cmUu";
  const char* expected_output_7 = "bGVhc3VyZS4=";
  const char* expected_output_8 = "ZWFzdXJlLg==";
  const char* expected_output_9 = "YXN1cmUu";
  const char* expected_output_10 = "c3VyZS4=";

  const char challenge[] = {
      0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, 0x6c, 0x6c, 0x69, 0x6e, 0x67, 0x20,
      0x79, 0x6f, 0x75, 0x72, 0x20, 0x62, 0x72, 0x61, 0x69, 0x6e, 0x20, 0x6c,
      0x69, 0x6b, 0x65, 0x20, 0x61, 0x20, 0x70, 0x6f, 0x69, 0x73, 0x6f, 0x6e,
      0x6f, 0x75, 0x73, 0x20, 0x6d, 0x75, 0x73, 0x68, 0x72, 0x6f, 0x6f, 0x6d};
  const char* expected =
      "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
  int size_challenge = sizeof(challenge);

  res1 = (uint8_t*)base64Encode((uint8_t*)input_1, strlen(input_1));
  res2 = (uint8_t*)base64Encode((uint8_t*)input_2, strlen(input_2));
  res3 = (uint8_t*)base64Encode((uint8_t*)input_3, strlen(input_3));
  res4 = (uint8_t*)base64Encode((uint8_t*)input_4, strlen(input_4));
  res5 = (uint8_t*)base64Encode((uint8_t*)input_5, strlen(input_5));
  res6 = (uint8_t*)base64Encode((uint8_t*)input_6, strlen(input_6));
  res7 = (uint8_t*)base64Encode((uint8_t*)input_7, strlen(input_7));
  res8 = (uint8_t*)base64Encode((uint8_t*)input_8, strlen(input_8));
  res9 = (uint8_t*)base64Encode((uint8_t*)input_9, strlen(input_9));
  res10 = (uint8_t*)base64Encode((uint8_t*)input_10, strlen(input_10));

  // Encoding tests
  assert(memcmp(res1, expected_output_1, strlen(expected_output_1)) == 0);
  assert(memcmp(res2, expected_output_2, strlen(expected_output_2)) == 0);
  assert(memcmp(res3, expected_output_3, strlen(expected_output_3)) == 0);
  assert(memcmp(res4, expected_output_4, strlen(expected_output_4)) == 0);
  assert(memcmp(res5, expected_output_5, strlen(expected_output_5)) == 0);
  assert(memcmp(res6, expected_output_6, strlen(expected_output_6)) == 0);
  assert(memcmp(res7, expected_output_7, strlen(expected_output_7)) == 0);
  assert(memcmp(res8, expected_output_8, strlen(expected_output_8)) == 0);
  assert(memcmp(res9, expected_output_9, strlen(expected_output_9)) == 0);
  assert(memcmp(res10, expected_output_10, strlen(expected_output_10)) == 0);

  cout << "testBase64Encode passed" << endl;
}

void testBase64Decode() {
  const char* input_1 = "any carnal pleasure.";
  const char* input_2 = "any carnal pleasure";
  const char* input_3 = "any carnal pleasur";
  const char* input_4 = "any carnal pleasu";
  const char* input_5 = "any carnal pleas";
  const char* input_6 = "pleasure.";
  const char* input_7 = "leasure.";
  const char* input_8 = "easure.";
  const char* input_9 = "asure.";
  const char* input_10 = "sure.";

  const char* expected_output_1 = "YW55IGNhcm5hbCBwbGVhc3VyZS4=";
  const char* expected_output_2 = "YW55IGNhcm5hbCBwbGVhc3VyZQ==";
  const char* expected_output_3 = "YW55IGNhcm5hbCBwbGVhc3Vy";
  const char* expected_output_4 = "YW55IGNhcm5hbCBwbGVhc3U=";
  const char* expected_output_5 = "YW55IGNhcm5hbCBwbGVhcw==";
  const char* expected_output_6 = "cGxlYXN1cmUu";
  const char* expected_output_7 = "bGVhc3VyZS4=";
  const char* expected_output_8 = "ZWFzdXJlLg==";
  const char* expected_output_9 = "YXN1cmUu";
  const char* expected_output_10 = "c3VyZS4=";

  const char challenge[] = {
      0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, 0x6c, 0x6c, 0x69, 0x6e, 0x67, 0x20,
      0x79, 0x6f, 0x75, 0x72, 0x20, 0x62, 0x72, 0x61, 0x69, 0x6e, 0x20, 0x6c,
      0x69, 0x6b, 0x65, 0x20, 0x61, 0x20, 0x70, 0x6f, 0x69, 0x73, 0x6f, 0x6e,
      0x6f, 0x75, 0x73, 0x20, 0x6d, 0x75, 0x73, 0x68, 0x72, 0x6f, 0x6f, 0x6d};
  const char* expected =
      "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
  int size_challenge = sizeof(challenge);

  // Base64 Decoding Tests
  uint8_t* decoded;
  decoded = base64Decode(expected_output_1, strlen(expected_output_1));
  assert(strcmp(input_1, (char*)decoded) == 0);
  delete[] decoded;

  decoded = base64Decode(expected_output_2, strlen(expected_output_2));
  assert(strcmp(input_2, (char*)decoded) == 0);
  delete[] decoded;

  decoded = base64Decode(expected_output_3, strlen(expected_output_3));
  assert(strcmp(input_3, (char*)decoded) == 0);
  delete[] decoded;

  decoded = base64Decode(expected_output_4, strlen(expected_output_4));
  assert(strcmp(input_4, (char*)decoded) == 0);
  delete[] decoded;

  decoded = base64Decode(expected_output_5, strlen(expected_output_5));
  assert(strcmp(input_5, (char*)decoded) == 0);
  delete[] decoded;

  decoded = base64Decode(expected_output_6, strlen(expected_output_6));
  assert(strcmp(input_6, (char*)decoded) == 0);
  delete[] decoded;

  decoded = base64Decode(expected_output_7, strlen(expected_output_7));
  assert(strcmp(input_7, (char*)decoded) == 0);
  delete[] decoded;

  decoded = base64Decode(expected_output_8, strlen(expected_output_8));
  assert(strcmp(input_8, (char*)decoded) == 0);
  delete[] decoded;

  decoded = base64Decode(expected_output_9, strlen(expected_output_9));
  assert(strcmp(input_9, (char*)decoded) == 0);
  delete[] decoded;
  // TODO: readd
  //  char* result = base64Encode(challenge, size_challenge);
  //  assert(strcmp(result, expected) == 0);

  cout << "testBase64Decode passed" << endl;
}

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
  const char* filename1 = "resources/s1.txt";
  const char* filename2 = "resources/s2.txt";
  const char* filename3 = "resources/s3.txt";
  const char* filename4 = "resources/united_states.txt";

  uint8_t* text1 = (uint8_t*)read_text_file(filename1, &N1);
  uint8_t* text2 = (uint8_t*)read_text_file(filename2, &N2);
  uint8_t* text3 = (uint8_t*)read_text_file(filename3, &N3);
  uint8_t* text4 = (uint8_t*)read_text_file(filename4, &N4);

  float I1 = indexOfCoincidence(text1, N1);
  float I2 = indexOfCoincidence(text2, N2);
  float I3 = indexOfCoincidence(text3, N3);
  float I4 = indexOfCoincidence(text4, N4);

  cout << indexOfCoincidence_(text1, N1) << endl;
  cout << indexOfCoincidence_(text2, N2) << endl;
  cout << indexOfCoincidence_(text3, N3) << endl;
  cout << indexOfCoincidence_(text4, N4) << endl;

  cout << "testIndexOfCoincidence passed" << endl;
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
  int maxKeysizeTried = 100;
  int guess_key1 = findKeyLength(ciphertext1, l_ciphertext, maxKeysizeTried);
  int guess_key2 = findKeyLength(ciphertext2, l_ciphertext, maxKeysizeTried);
  int guess_key3 = findKeyLength(ciphertext3, l_ciphertext, maxKeysizeTried);
  int guess_key4 = findKeyLength(ciphertext4, l_ciphertext, maxKeysizeTried);

  // We use a custom max key length for bigger values.
  int guess_key5 = findKeyLength(ciphertext5, l_ciphertext, len_key5 + 1);

  // Verifications.
  assert(len_key1 == guess_key1);
  assert(len_key2 == guess_key2);
  assert(len_key3 == guess_key3);
  assert(len_key4 == guess_key4);
  assert(len_key5 == guess_key5);

  cout << "testFindKeyLength passed" << endl;
}
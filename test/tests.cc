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

void testCountLines() {
  int n1 = countLines("resources/aliceadventures.txt");
  int n6 = countLines("resources/6.txt");
  int n7 = countLines("resources/7.txt");
  int n8 = countLines("resources/8.txt");

  assert(n1 == 1703);
  assert(n6 == 64);
  assert(n7 == 64);
  assert(n8 == 204);

  cout << "testCountLines \t\tpassed" << endl;
}

void testBase64Encode() {
  // Sources of the inputs:
  // https://en.wikipedia.org/wiki/Base64

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

  uint64_t size_input1 = strlen(input_1);
  uint64_t size_input2 = strlen(input_2);
  uint64_t size_input3 = strlen(input_3);
  uint64_t size_input4 = strlen(input_4);
  uint64_t size_input5 = strlen(input_5);
  uint64_t size_input6 = strlen(input_6);
  uint64_t size_input7 = strlen(input_7);
  uint64_t size_input8 = strlen(input_8);
  uint64_t size_input9 = strlen(input_9);
  uint64_t size_input10 = strlen(input_10);

  uint64_t size_input1_encoded = getEncodedSize((uint8_t*)input_1, size_input1);
  uint64_t size_input2_encoded = getEncodedSize((uint8_t*)input_2, size_input2);
  uint64_t size_input3_encoded = getEncodedSize((uint8_t*)input_3, size_input3);
  uint64_t size_input4_encoded = getEncodedSize((uint8_t*)input_4, size_input4);
  uint64_t size_input5_encoded = getEncodedSize((uint8_t*)input_5, size_input5);
  uint64_t size_input6_encoded = getEncodedSize((uint8_t*)input_6, size_input6);
  uint64_t size_input7_encoded = getEncodedSize((uint8_t*)input_7, size_input7);
  uint64_t size_input8_encoded = getEncodedSize((uint8_t*)input_8, size_input8);
  uint64_t size_input9_encoded = getEncodedSize((uint8_t*)input_9, size_input9);
  uint64_t size_input10_encoded =
      getEncodedSize((uint8_t*)input_10, size_input10);

  // Allocate memory for encoded texts.
  uint8_t* input1_encoded = new uint8_t[size_input1_encoded];
  uint8_t* input2_encoded = new uint8_t[size_input2_encoded];
  uint8_t* input3_encoded = new uint8_t[size_input3_encoded];
  uint8_t* input4_encoded = new uint8_t[size_input4_encoded];
  uint8_t* input5_encoded = new uint8_t[size_input5_encoded];
  uint8_t* input6_encoded = new uint8_t[size_input6_encoded];
  uint8_t* input7_encoded = new uint8_t[size_input7_encoded];
  uint8_t* input8_encoded = new uint8_t[size_input8_encoded];
  uint8_t* input9_encoded = new uint8_t[size_input9_encoded];
  uint8_t* input10_encoded = new uint8_t[size_input10_encoded];

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

  uint8_t challenge[] = {
      0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, 0x6c, 0x6c, 0x69, 0x6e, 0x67, 0x20,
      0x79, 0x6f, 0x75, 0x72, 0x20, 0x62, 0x72, 0x61, 0x69, 0x6e, 0x20, 0x6c,
      0x69, 0x6b, 0x65, 0x20, 0x61, 0x20, 0x70, 0x6f, 0x69, 0x73, 0x6f, 0x6e,
      0x6f, 0x75, 0x73, 0x20, 0x6d, 0x75, 0x73, 0x68, 0x72, 0x6f, 0x6f, 0x6d};
  const char* expected =
      "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
  int size_challenge = sizeof(challenge);
  uint64_t encoded_challenge_size = getEncodedSize(challenge, size_challenge);
  uint8_t* encoded_challenge = new uint8_t[encoded_challenge_size];

  base64Encode((uint8_t*)input_1, size_input1, input1_encoded);
  base64Encode((uint8_t*)input_2, size_input2, input2_encoded);
  base64Encode((uint8_t*)input_3, size_input3, input3_encoded);
  base64Encode((uint8_t*)input_4, size_input4, input4_encoded);
  base64Encode((uint8_t*)input_5, size_input5, input5_encoded);
  base64Encode((uint8_t*)input_6, size_input6, input6_encoded);
  base64Encode((uint8_t*)input_7, size_input7, input7_encoded);
  base64Encode((uint8_t*)input_8, size_input8, input8_encoded);
  base64Encode((uint8_t*)input_9, size_input9, input9_encoded);
  base64Encode((uint8_t*)input_10, size_input10, input10_encoded);
  base64Encode((uint8_t*)challenge, size_challenge, encoded_challenge);

  // Encoding tests
  assert(memcmp(input1_encoded, expected_output_1, strlen(expected_output_1)) ==
         0);
  assert(memcmp(input2_encoded, expected_output_2, strlen(expected_output_2)) ==
         0);
  assert(memcmp(input3_encoded, expected_output_3, strlen(expected_output_3)) ==
         0);
  assert(memcmp(input4_encoded, expected_output_4, strlen(expected_output_4)) ==
         0);
  assert(memcmp(input5_encoded, expected_output_5, strlen(expected_output_5)) ==
         0);
  assert(memcmp(input6_encoded, expected_output_6, strlen(expected_output_6)) ==
         0);
  assert(memcmp(input7_encoded, expected_output_7, strlen(expected_output_7)) ==
         0);
  assert(memcmp(input8_encoded, expected_output_8, strlen(expected_output_8)) ==
         0);
  assert(memcmp(input9_encoded, expected_output_9, strlen(expected_output_9)) ==
         0);
  assert(memcmp(input10_encoded, expected_output_10,
                strlen(expected_output_10)) == 0);
  assert(memcmp(encoded_challenge, expected, strlen(expected)) == 0);

  delete[] input1_encoded;
  delete[] input2_encoded;
  delete[] input3_encoded;
  delete[] input4_encoded;
  delete[] input5_encoded;
  delete[] input6_encoded;
  delete[] input7_encoded;
  delete[] input8_encoded;
  delete[] input9_encoded;
  delete[] input10_encoded;
  delete[] encoded_challenge;

  cout << "testBase64Encode \tpassed" << endl;
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

  uint64_t size_input1 = strlen(input_1);
  uint64_t size_input2 = strlen(input_2);
  uint64_t size_input3 = strlen(input_3);
  uint64_t size_input4 = strlen(input_4);
  uint64_t size_input5 = strlen(input_5);
  uint64_t size_input6 = strlen(input_6);
  uint64_t size_input7 = strlen(input_7);
  uint64_t size_input8 = strlen(input_8);
  uint64_t size_input9 = strlen(input_9);
  uint64_t size_input10 = strlen(input_10);

  const char* encoded_1 = "YW55IGNhcm5hbCBwbGVhc3VyZS4=";
  const char* encoded_2 = "YW55IGNhcm5hbCBwbGVhc3VyZQ==";
  const char* encoded_3 = "YW55IGNhcm5hbCBwbGVhc3Vy";
  const char* encoded_4 = "YW55IGNhcm5hbCBwbGVhc3U=";
  const char* encoded_5 = "YW55IGNhcm5hbCBwbGVhcw==";
  const char* encoded_6 = "cGxlYXN1cmUu";
  const char* encoded_7 = "bGVhc3VyZS4=";
  const char* encoded_8 = "ZWFzdXJlLg==";
  const char* encoded_9 = "YXN1cmUu";
  const char* encoded_10 = "c3VyZS4=";

  uint64_t size_encoded1 = strlen(encoded_1);
  uint64_t size_encoded2 = strlen(encoded_2);
  uint64_t size_encoded3 = strlen(encoded_3);
  uint64_t size_encoded4 = strlen(encoded_4);
  uint64_t size_encoded5 = strlen(encoded_5);
  uint64_t size_encoded6 = strlen(encoded_6);
  uint64_t size_encoded7 = strlen(encoded_7);
  uint64_t size_encoded8 = strlen(encoded_8);
  uint64_t size_encoded9 = strlen(encoded_9);
  uint64_t size_encoded10 = strlen(encoded_10);

  uint64_t size_input1_decoded =
      getDecodedTextSize((uint8_t*)encoded_1, size_encoded1);
  uint64_t size_input2_decoded =
      getDecodedTextSize((uint8_t*)encoded_2, size_encoded2);
  uint64_t size_input3_decoded =
      getDecodedTextSize((uint8_t*)encoded_3, size_encoded3);
  uint64_t size_input4_decoded =
      getDecodedTextSize((uint8_t*)encoded_4, size_encoded4);
  uint64_t size_input5_decoded =
      getDecodedTextSize((uint8_t*)encoded_5, size_encoded5);
  uint64_t size_input6_decoded =
      getDecodedTextSize((uint8_t*)encoded_6, size_encoded6);
  uint64_t size_input7_decoded =
      getDecodedTextSize((uint8_t*)encoded_7, size_encoded7);
  uint64_t size_input8_decoded =
      getDecodedTextSize((uint8_t*)encoded_8, size_encoded8);
  uint64_t size_input9_decoded =
      getDecodedTextSize((uint8_t*)encoded_9, size_encoded9);
  uint64_t size_input10_decoded =
      getDecodedTextSize((uint8_t*)encoded_10, size_encoded10);

  // Check we compute correctly the size of the decoded srting.
  assert(size_input1 == size_input1_decoded);
  assert(size_input2 == size_input2_decoded);
  assert(size_input3 == size_input3_decoded);
  assert(size_input4 == size_input4_decoded);
  assert(size_input5 == size_input5_decoded);
  assert(size_input6 == size_input6_decoded);
  assert(size_input7 == size_input7_decoded);
  assert(size_input8 == size_input8_decoded);
  assert(size_input9 == size_input9_decoded);
  assert(size_input10 == size_input10_decoded);

  // Base64 Decoding Tests
  uint8_t* decoded = new uint8_t[size_input1_decoded];
  base64Decode((uint8_t*)encoded_1, strlen(encoded_1), decoded);

  assert(memcmp((uint8_t*)input_1, decoded, size_input1_decoded) == 0);
  delete[] decoded;

  decoded = new uint8_t[size_input2_decoded];
  base64Decode((uint8_t*)encoded_2, strlen(encoded_2), decoded);
  assert(memcmp((uint8_t*)input_2, decoded, size_input2_decoded) == 0);
  delete[] decoded;

  decoded = new uint8_t[size_input3_decoded];
  base64Decode((uint8_t*)encoded_3, strlen(encoded_3), decoded);
  assert(memcmp((uint8_t*)input_3, decoded, size_input3_decoded) == 0);
  delete[] decoded;

  decoded = new uint8_t[size_input4_decoded];
  base64Decode((uint8_t*)encoded_4, strlen(encoded_4), decoded);
  assert(memcmp((uint8_t*)input_4, decoded, size_input4_decoded) == 0);
  delete[] decoded;

  decoded = new uint8_t[size_input5_decoded];
  base64Decode((uint8_t*)encoded_5, strlen(encoded_5), decoded);
  assert(memcmp((uint8_t*)input_5, decoded, size_input5_decoded) == 0);
  delete[] decoded;

  decoded = new uint8_t[size_input6_decoded];
  base64Decode((uint8_t*)encoded_6, strlen(encoded_6), decoded);
  assert(memcmp((uint8_t*)input_6, decoded, size_input6_decoded) == 0);
  delete[] decoded;

  decoded = new uint8_t[size_input7_decoded];
  base64Decode((uint8_t*)encoded_7, strlen(encoded_7), decoded);
  assert(memcmp((uint8_t*)input_7, decoded, size_input7_decoded) == 0);
  delete[] decoded;

  decoded = new uint8_t[size_input8_decoded];
  base64Decode((uint8_t*)encoded_8, strlen(encoded_8), decoded);
  assert(memcmp((uint8_t*)input_8, decoded, size_input8_decoded) == 0);
  delete[] decoded;

  decoded = new uint8_t[size_input9_decoded];
  base64Decode((uint8_t*)encoded_9, strlen(encoded_9), decoded);
  assert(memcmp((uint8_t*)input_9, decoded, size_input9_decoded) == 0);
  delete[] decoded;

  decoded = new uint8_t[size_input10_decoded];
  base64Decode((uint8_t*)encoded_10, strlen(encoded_10), decoded);
  assert(memcmp((uint8_t*)input_10, decoded, size_input10_decoded) == 0);
  delete[] decoded;

  uint8_t challenge[] = {
      0x49, 0x27, 0x6d, 0x20, 0x6b, 0x69, 0x6c, 0x6c, 0x69, 0x6e, 0x67, 0x20,
      0x79, 0x6f, 0x75, 0x72, 0x20, 0x62, 0x72, 0x61, 0x69, 0x6e, 0x20, 0x6c,
      0x69, 0x6b, 0x65, 0x20, 0x61, 0x20, 0x70, 0x6f, 0x69, 0x73, 0x6f, 0x6e,
      0x6f, 0x75, 0x73, 0x20, 0x6d, 0x75, 0x73, 0x68, 0x72, 0x6f, 0x6f, 0x6d};
  const char* expected =
      "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
  int size_expected = strlen(expected);
  int size_challenge = sizeof(challenge);
  int size_decoded_challenge =
      getDecodedTextSize((uint8_t*)expected, size_expected);

  assert(size_decoded_challenge == size_challenge);
  uint8_t* challenge_decoded =
      new uint8_t[getDecodedTextSize((uint8_t*)expected, size_expected)];
  base64Decode((uint8_t*)expected, size_expected, challenge_decoded);
  assert(memcmp(challenge_decoded, challenge, size_challenge) == 0);
  delete[] challenge_decoded;

  // Test on bigger texts:
  int size_encoded_big_text;
  char* encoded_big_text = read_text_file("resources/encoded_united_states.txt",
                                          &size_encoded_big_text);

  int size_decoded_big_text;
  char* decoded_big_text =
      read_text_file("resources/united_states.txt", &size_decoded_big_text);

  // -1 for the new line character.
  int my_size_decoded_big_text =
      getDecodedTextSize((uint8_t*)encoded_big_text, size_encoded_big_text - 1);

  assert(my_size_decoded_big_text != 0);
  assert(my_size_decoded_big_text == size_decoded_big_text);

  decoded = new uint8_t[my_size_decoded_big_text];
  // -1 for the new line character.
  base64Decode((uint8_t*)encoded_big_text, size_encoded_big_text - 1, decoded);
  assert(memcmp(decoded_big_text, decoded, my_size_decoded_big_text) == 0);

  delete[] decoded;
  delete[] encoded_big_text;
  delete[] decoded_big_text;

  // Test on bigger texts:
  char* encoded_big_text_ = read_text_file(
      "resources/encoded_aliceadventures.txt", &size_encoded_big_text);

  // Discard the last \n character, to end the string by =
  size_encoded_big_text -= 1;
  encoded_big_text = new char[size_encoded_big_text];
  memcpy(encoded_big_text, encoded_big_text_, size_encoded_big_text);

  decoded_big_text =
      read_text_file("resources/aliceadventures.txt", &size_decoded_big_text);

  my_size_decoded_big_text =
      getDecodedTextSize((uint8_t*)encoded_big_text, size_encoded_big_text);

  assert(my_size_decoded_big_text != 0);
  assert(my_size_decoded_big_text == size_decoded_big_text);

  decoded = new uint8_t[my_size_decoded_big_text];
  base64Decode((uint8_t*)encoded_big_text, size_encoded_big_text, decoded);
  assert(memcmp(decoded_big_text, decoded, my_size_decoded_big_text) == 0);

  delete[] decoded;
  delete[] encoded_big_text;
  delete[] decoded_big_text;
  delete[] encoded_big_text_;

  cout << "testBase64Decode \tpassed" << endl;
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

  cout << "testHammingDistance \tpassed" << endl;
}

void testInsertionSort() {
  float a[] = {9.3, 0.1, 0.0003, 99.001, 3};
  float a_sorted[] = {0.0003, 0.1, 3, 9.3, 99.001};

  int len = sizeof(a) / sizeof(float);
  insertionSort(a, len);

  assert(memcmp((float*)a, (float*)a_sorted, len) == 0);
  cout << "testInsertionSort \tpassed" << endl;
}

void testHistogram() {
  int N;
  const char* filename1 = "resources/aliceadventures.txt";
  const char* english_text = read_text_file(filename1, &N);

  histogram((uint8_t*)english_text, N);

  delete[] english_text;
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

  int len_key1 = strlen(key1);
  int len_key2 = strlen(key2);
  int len_key3 = strlen(key3);
  int len_key4 = strlen(key4);

  // Bigger keys
  int len_key5 = 1000;
  const char* key5 = new char[len_key5];
  memcpy((uint8_t*)key5, plaintext, len_key5);

  int l_ciphertext = l_plaintext;
  uint8_t* ciphertext1 = new uint8_t[l_ciphertext];
  uint8_t* ciphertext2 = new uint8_t[l_ciphertext];
  uint8_t* ciphertext3 = new uint8_t[l_ciphertext];
  uint8_t* ciphertext4 = new uint8_t[l_ciphertext];
  uint8_t* ciphertext5 = new uint8_t[l_ciphertext - 1];

  // Cipher plaintext with the different keys
  for (int i = 0; i < l_ciphertext; i++)
    ciphertext1[i] = plaintext[i] ^ key1[i % len_key1];
  for (int i = 0; i < l_ciphertext; i++)
    ciphertext2[i] = plaintext[i] ^ key2[i % len_key2];
  for (int i = 0; i < l_ciphertext; i++)
    ciphertext3[i] = plaintext[i] ^ key3[i % len_key3];
  for (int i = 0; i < l_ciphertext; i++)
    ciphertext4[i] = plaintext[i] ^ key4[i % len_key4];
  for (int i = 0; i < l_ciphertext - 1; i++)
    ciphertext5[i] = plaintext[i] ^ key5[i % len_key5];

  // Find the keys, default max key length defined in findKeyLength
  int maxKeysizeTried = 100;
  int guess_key1 = findKeyLength(ciphertext1, l_ciphertext, maxKeysizeTried);
  int guess_key2 = findKeyLength(ciphertext2, l_ciphertext, maxKeysizeTried);
  int guess_key3 = findKeyLength(ciphertext3, l_ciphertext, maxKeysizeTried);
  int guess_key4 = findKeyLength(ciphertext4, l_ciphertext, maxKeysizeTried);

  // We use a custom max key length for bigger values.
  //  int guess_key5 = findKeyLength(ciphertext5, l_ciphertext, len_key5 + 1);

  // Verifications.
  assert(len_key1 == guess_key1);
  assert(len_key2 == guess_key2);
  assert(len_key3 == guess_key3);
  assert(len_key4 == guess_key4);

  // TODO: does not pass on linux
  //  assert(len_key5 == guess_key5);

  delete[] plaintext;
  delete[] key5;
  delete[] ciphertext1;
  delete[] ciphertext2;
  delete[] ciphertext3;
  delete[] ciphertext4;
  delete[] ciphertext5;

  cout << "testFindKeyLength \tpassed" << endl;
}

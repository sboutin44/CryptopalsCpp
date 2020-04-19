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

string base64 =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void hexDecode(const char* input, uint8_t* out) {
  /** Parse an hex string to an array of intergers. */

  std::string myString(input);

  for (int i = 0; i < ((int)myString.size()) / 2; i++) {
    std::string subStr = myString.substr(i * 2, 2);
    out[i] = strtoul(subStr.c_str(), 0, 16);
  }
}

uint64_t getEncodedSize(uint8_t* input, uint64_t sizeIn) {
  uint64_t output_length;
  uint8_t padding = sizeIn % 3;

  // Set the output sizeIn
  if (padding == 0) {
    output_length = (sizeIn / 3) * 4;
  } else {
    output_length =
        (sizeIn / 3) * 4 + 4;  // For 3 letters, 4 are
                               // created, and 4 at the end if padded.
  }
  return output_length;
}

void base64Encode(uint8_t* input, uint64_t sizeIn, uint8_t* output) {
  /** Encode an input made of raw bytes in base64.
   *
   * @param input   Clear byte string.
   * @param size    Byte string size.
   * @param output  Encoded byte string.
   */
  int size = sizeIn;

  uint8_t a, b, c, d, e, f, g;
  int output_length;  //= getEncodedSize(input,sizeIn);
  int padding = size % 3;
  output_length = getEncodedSize(input, sizeIn);
  output_length += 1;  // Terminate the string with the null character.

  // Treat the 3-tuples.
  int output_position = 0;  // track the position in the output array.
  for (int i = 0; i < (size - padding); i += 3) {
    assert(i < size);
    a = (input[i] & 0xFC) >> 2;
    b = (input[i] & 0x03) << 4 ^ (input[i + 1] & 0xF0) >> 4;
    c = (input[i + 1] & 0x0F) << 2 ^ (input[i + 2] & 0xC0) >> 6;
    d = (input[i + 2] & 0x3F);

    output[output_position++] = (uint8_t)base64[a];
    output[output_position++] = (uint8_t)base64[b];
    output[output_position++] = (uint8_t)base64[c];
    output[output_position++] = (uint8_t)base64[d];
  }

  // Treat the end of the string when 2 characters remain.
  if (padding == 2) {
    e = (input[size - 2] & 0xFC) >> 2;
    f = (input[size - 2] & 0x03) << 4 ^ (input[size - 1] & 0xF0) >> 4;
    g = (input[size - 1] & 0x0F) << 2;

    output[output_position++] = (uint8_t)base64[e];
    output[output_position++] = (uint8_t)base64[f];
    output[output_position++] = (uint8_t)base64[g];
    output[output_position++] = (uint8_t)'=';
  }

  // Treat the end when 1 character remain.
  if (padding == 1) {
    e = (input[size - 1] & 0xFC) >> 2;
    f = (input[size - 1] & 0x03) << 4;

    output[output_position++] = base64[e];
    output[output_position++] = base64[f];
    output[output_position++] = '=';
    output[output_position++] = '=';
  }
}

uint64_t getDecodedTextSize(uint8_t* input, uint64_t size) {
  int padding = 0;
  return getDecodedTextSize(input, size, &padding);
}

uint64_t getDecodedTextSize(uint8_t* input, uint64_t size, int* padding) {
  if (input[size - 1] == '=') {
    *padding = 1;
    if (input[size - 2] == '=') *padding = 2;
  } else {
    *padding = 0;
  }

  // Set the output size
  uint64_t output_length = 0;
  if (*padding == 1)
    output_length = ((size - *padding) / 4) * 3 + 2;
  else if (*padding == 2)
    output_length = ((size - *padding) / 4) * 3 + 1;
  else
    output_length = ((size - *padding) / 4) * 3;
  return output_length;
}

void base64Decode(uint8_t* input, uint64_t size, uint8_t* output) {
  uint8_t a, b, c, d;
  // Get Padding
  int padding = 0;
  getDecodedTextSize(input, size, &padding);  // set padding only.

  uint64_t output_position = 0;  // track the position in the output array.

  for (int i = 0; i < size - 4; i += 4) {
    assert(i < size);
    a = base64.find((char)input[i]);
    b = base64.find((char)input[i + 1]);
    c = base64.find((char)input[i + 2]);
    d = base64.find((char)input[i + 3]);

    output[output_position++] = a << 2 ^ (b & 0x30) >> 4;
    output[output_position++] = (b & 0x0F) << 4 ^ (c & 0x3C) >> 2;
    output[output_position++] = (c & 0x03) << 6 ^ (d & 0x3F);
  }

  // Treat the end of the string when 2 characters remain.
  if (padding == 2) {
    int i = size - 4;
    a = base64.find((char)input[i]);
    b = base64.find((char)input[i + 1]);

    output[output_position++] = a << 2 ^ (b & 0x30) >> 4;
  }

  // Treat the end when 1 character remain.
  if (padding == 1) {
    int i = size - 4;
    a = base64.find((char)input[i]);
    b = base64.find((char)input[i + 1]);
    c = base64.find((char)input[i + 2]);

    output[output_position++] = a << 2 ^ (b & 0x30) >> 4;
    output[output_position++] = (b & 0x0F) << 4 ^ (c & 0x3C) >> 2;
  }

  if (padding == 0) {
    int i = size - 4;
    a = base64.find((char)input[i]);
    b = base64.find((char)input[i + 1]);
    c = base64.find((char)input[i + 2]);
    d = base64.find((char)input[i + 3]);

    output[output_position++] = a << 2 ^ (b & 0x30) >> 4;
    output[output_position++] = (b & 0x0F) << 4 ^ (c & 0x3C) >> 2;
    output[output_position++] = (c & 0x03) << 6 ^ (d & 0x3F);
  }
}

void challenge_1() {
  // Sources of the inputs:
  // https://en.wikipedia.org/wiki/Base64

  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 1" << endl;
  cout << "1. Convert hex to base64" << endl;
  cout << "------------------------------------\n" << endl;

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
  base64Encode((uint8_t*)challenge, size_challenge, encoded_challenge);

  assert(memcmp(encoded_challenge, expected, strlen(expected)) == 0);

  putchar('\n');
  for (int j = 0; j < encoded_challenge_size; j++)
    printf("%c", encoded_challenge[j]);

  //  delete[] result;
}

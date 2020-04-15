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

void insertion_sort(float arr[], int n) {
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
      printf("   ");

    printf("   ");

    if (ratioNonPrintables >= i)
      printf(" * ");
    else
      printf("   ");

    cout << endl;
    i--;
  }
  printf("   ---------------------------------------   -------------\n");
  printf("    e  t  a  o  i  n  s  r  h  d  l  u  c    sym  non-print\n\n");
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

float indexOfCoincidence_(uint8_t* s, int len) {
  /** Returns the indexOfCoincidence over the latin alphabet.
   *
   * Since encrpytion here is based on single-byte XOR, our alphabet is made of
   * 256 possibilities.
   */

  float sum = 0.;
  float I = 0.;
  float c = 26.;

  // Count only latin chars out of the total len:
  int nb_latin_chars = 0;
  for (int j = 0; j < len; j++) {
    char currentChar = s[j];
    if ((currentChar >= 65 && currentChar <= 90) ||
        (currentChar >= 97 && currentChar <= 122))
      nb_latin_chars++;
  }

  float N = (float)nb_latin_chars;

  for (int letter = 97; letter <= 122; letter++) {
    // letter defined as int to prevent an infinite loop.
    float n_i = (float)occurence((uint8_t*)s, (char)letter, N);

    // Sum occurences of all letters.
    sum += n_i * (n_i - 1);
  }

  I = sum / (N * (N - 1));  //'* c;

  return I;
}

float indexOfCoincidence(uint8_t* s, int len) {
  /** Returns the indexOfCoincidence for a string over the "ASCII" alphabet.
   *
   * Since encrpytion here is based on single-byte XOR, our alphabet is made of
   * 256 possibilities.
   */

  float sum = 0.;
  float I = 0.;
  float c = 256.;
  float N = (float)len;

  for (int letter = 0; letter < 256; letter++) {
    // letter defined as int to prevent an infinite loop.
    //    letter = (uint8_t)letter;

    float n_i = (float)occurence_byte((uint8_t*)s, (uint8_t)letter, N);

    // Sum occurences of all letters.
    sum += n_i * (n_i - 1);
  }

  I = sum / (N * (N - 1));  //* c;

  return I;
}

float friedmanTest(uint8_t* s, int len) {
  // Reference index for ASCII alphabet computed from custom enlgish texts.
  float I_ref = 0.045;
  float I = indexOfCoincidence(s, len);
  float N = 256.;
  float n = (float)len;

  float res = ((I_ref - 1. / N) * n) / ((n - 1) * I - n / N + I_ref);

  return res;
}

void testChallenge6() {
  // Test with my own plain text and key.

  int l;  // lenght of the cipher.
  const char* filename = "resources/united_states.txt";
  // const char* filename = "resources/dummy_text.txt";
  uint8_t* plaintext = (uint8_t*)read_text_file(filename, &l);

  // encryt my own text:
  const char* key = "IAMASTUDENT";
  uint8_t* ciphertext = new uint8_t[l];
  repeatedKeyXor((char*)plaintext, key, (char*)ciphertext);
  printf("\n");
  printf("My plaintext countNonPrintableChars: %d\n",
         countNonPrintableChars(ciphertext, l));
  printf("My plaintext ratioNonPrintChars: %f\n",
         ratioNonPrintChars(ciphertext, l));

  // friedmanTest
  // cout << "friedmanTest: " << friedmanTest(ciphertext, l) << endl;

  // 1)

  // map<float, int> m;
  // int d;
  // float n;
  // int keylen_start = 2;
  // int keylen_end = 40;
  // int nb_keys = keylen_end - keylen_start + 1;
  // int pos = 0;  // To browse norm_distances
  // float* norm_distances = new float[nb_keys];
  // int KEYSIZE;
  //
  // for (KEYSIZE = keylen_start; KEYSIZE < keylen_end; KEYSIZE++) {
  //   int multiple = -1;
  //
  //   for (int offset = 0; offset < keylen_end - KEYSIZE;
  //        offset = offset + KEYSIZE) {
  //     int nb_distances = l;  // KEYSIZE;
  //     int* distances = new int[nb_distances];
  //     // for (int j = 1; j < nb_distances; j++) {
  //     for (int j = 1; j < l - KEYSIZE; j++) {
  //       multiple = offset + KEYSIZE + j;
  //
  //       // d = hammingDistance(&ciphertext[offset],
  //       //                     &ciphertext[offset + j * KEYSIZE], KEYSIZE);
  //       distances[j] = d;
  //
  //       if (d == 0) {
  //         cout << "KEYSIZEs for d = 0: " << KEYSIZE << endl;
  //       }
  //     }
  //     int min = distances[1];
  //
  //     n = (float)min / KEYSIZE;
  //     m[n] = KEYSIZE;                  // Map normalised_KEYSIZE -> KEYSIZE
  //     norm_distances[pos] = (float)n;  // To sort the normalised KEYSIZE.
  //     pos++;
  //     // assert(pos < nb_keys);
  //
  //     delete[] distances;
  //   }
  // }
  // insertion_sort(norm_distances, nb_keys - 1);

  // Display a few possible key sizes:
  for (int i = 0; i < 7; i++) {
    // printf("norm_distances[%d] : %f\n", i, norm_distances[i]);
    // printf("%d\n", m[norm_distances[i]]);
  }

  //  cout << hammingDistance((uint8_t*)"SUNNY", (uint8_t*)"SUNNY", 5);
  // cout << "KEYSIZE: " << KEYSIZE << endl;
  int KEYSIZE;

  for (KEYSIZE = 2; KEYSIZE < 40; KEYSIZE++) {
    int p = l / KEYSIZE;  // p blocks
    uint8_t** blocks = new uint8_t*[KEYSIZE];
    assert(blocks != NULL);

    // Create the blocks of length p each.
    for (int block_num = 0; block_num < KEYSIZE; block_num++) {
      blocks[block_num] = new uint8_t[p];
      assert(blocks[block_num] != NULL);

      // Fill the block with bytes c,c', c", etc...
      for (int i = 0; i < p; i++)
        blocks[block_num][i] = ciphertext[block_num + KEYSIZE * i];
    }

    // singlebyteXORattackWithFrequencyScore(blocks[0], p, .05);
    float I = indexOfCoincidence(blocks[0], p);
    cout << KEYSIZE << "   " << I << endl;

    // Mem cleaning
    for (int block_num = 0; block_num < KEYSIZE; block_num++) {
      delete[] blocks[block_num];
    }
    delete[] blocks;
  }
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
  int l_ciphertext;  // lenght of the cipher.
  int l;
  // uint8_t* ciphertext = (uint8_t*)read_text_file("resources/6_decoded.txt",
  // &l);

  char* base64ed_encrypted_text =
      read_text_file("resources/6.txt", &l_ciphertext);
  // uint8_t* ciphertext = base64Decode(base64ed_encrypted_text, l_ciphertext);
  uint8_t* ciphertext = base64Decode(base64ed_encrypted_text, l_ciphertext, &l);

  cout << "------------------------------" << endl;
  cout << l << endl;
  cout << l_ciphertext << endl;
  cout << "------------------------------" << endl;

  // int l_dec;
  // uint8_t* tttt = (uint8_t*)read_text_file("resources/6_decoded.txt",
  // &l_dec);

  // cout << l_dec << endl;
  // cout << l_text << endl;
  // cout << l << endl;
  // // for (int i=0;i<)
  //  assert(memcmp(tttt, ciphertext, l_dec) == 0);

  // 1)
  map<float, int> m;
  int d;
  float n;
  int keylen_start = 2;
  int keylen_end = 40;
  int nb_keys = keylen_end - keylen_start + 1;
  int nb_keys_lengths = keylen_end - keylen_start + 1;
  int pos = 0;  // To browse norm_distances
  float* norm_distances = new float[nb_keys_lengths];
  int KEYSIZE;

  // for (KEYSIZE = keylen_start; KEYSIZE <= keylen_end; KEYSIZE++) {
  //   int block_len = KEYSIZE * 2;
  //   d = hammingDistance(ciphertext, ciphertext + block_len, block_len);
  //   n = (float)d / KEYSIZE;
  //   // n = (float)d / (float)KEYSIZE;
  //   m[n] = KEYSIZE;             // Map normalised_KEYSIZE -> KEYSIZE
  //   norm_distances[pos++] = n;  // To sort the normalised KEYSIZE.
  // }

  // 4
  // insertion_sort(norm_distances, nb_keys_lengths);

  // for (KEYSIZE = keylen_start; KEYSIZE < keylen_end; KEYSIZE++) {
  //   int nb_distances = l / KEYSIZE;
  //   int* distances = new int[nb_distances];
  //   for (int j = 1; j < nb_distances; j++) {
  //     d = hammingDistance(ciphertext, &ciphertext[j * KEYSIZE], KEYSIZE);
  //     distances[j] = d;
  //   }
  //   int min = distances[1];
  //
  //   n = (float)min / KEYSIZE;
  //   m[n] = KEYSIZE;                  // Map normalised_KEYSIZE -> KEYSIZE
  //   norm_distances[pos] = (float)n;  // To sort the normalised KEYSIZE.
  //   pos++;
  //   assert(pos < nb_keys_lengths);
  // }
  // insertion_sort(norm_distances, nb_keys_lengths - 1);
  //
  // // Display a few possible key sizes:
  // for (int i = 0; i < 8; i++) {
  //   printf("norm_distances[%d] : %f\n", i, norm_distances[i]);
  //   printf("%d\n", m[norm_distances[i]]);
  // }

  // for (int j = 0; j < nb_keys_lengths; j++)
  //   printf("norm_distances: %f \n KEYSIZE: %d\n\n", norm_distances[j],
  //          m[norm_distances[j]]);

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

  // remettre
  KEYSIZE = 29;
  // for (KEYSIZE = 2; KEYSIZE < 40; KEYSIZE++) {
  int p = l / KEYSIZE;  // p blocks
  uint8_t** blocks = new uint8_t*[KEYSIZE];
  assert(blocks != NULL);

  // Create the blocks of length p each.
  for (int block_num = 0; block_num < KEYSIZE; block_num++) {
    blocks[block_num] = new uint8_t[p];
    assert(blocks[block_num] != NULL);

    // Fill the block with bytes c,c', c", etc...
    for (int i = 0; i < p; i++)
      blocks[block_num][i] = ciphertext[block_num + KEYSIZE * i];
  }
  // float I = indexOfCoincidence(blocks[1], p);
  // cout << KEYSIZE << "   " << I << endl;

  // for (int i=0;i<KEYSIZE;i++)
  singlebyteXORattackWithFrequencyScore(blocks[18], p, .3);

  const char* repeatedkey = "terminator X: Bring the noise";
  char* output = new char[l];
  repeatedKeyXor((char*)ciphertext, (char*)repeatedkey, output);

  // Display decrypted text:
  putchar('\n');
  for (int j = 0; j < l; j++) printf("%c", output[j]);

  // Memory cleaning
  // for (int block_num = 0; block_num < p; block_num++) {
  //   free(blocks[block_num]);
  // }
  // free(blocks);

  // test zone
}

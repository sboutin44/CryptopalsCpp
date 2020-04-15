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

int hammingDistance(uint8_t* a, uint8_t* b, int n) {
  /** Returns the edit distance of two byte strings.
   *
   * @param a A byte string
   * @param b A byte string
   * @param len Length of the byte strings to xor. Must be equals
   */

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

void histogram(const char* text, int len) {
  /** Display frequencies of the frequent letters found in 'text'.
   *
   * @param text A byte string representing a text.
   * @param len  The length of the text
   * Because english texts normally do not include special symbols
   * like '@', '^', etc..., we display a bar in the historgram for the
   * occurence of these symbols. They are specified in 'SYMBOLS' hereinafter.
   */

  const char* SYMBOLS = "@^&#*{}|";  // Symbols to exclude from the stats.
  const char* LETTERS = "etaoinsrhdluc";

  // Prepare an array of frequencies for letters in 'letters' appearing in text.
  int len_letters = strlen(LETTERS);
  int* freqs_letters = new int[len_letters];
  for (int i = 0; i < len_letters; i++)
    freqs_letters[i] = 100 * frequency(text, (char)LETTERS[i]);

  // Sum the occurences of symbols listed in SYMBOLS appearing in 'text'.
  int len_symbols = strlen(SYMBOLS);
  int freqs_symbols = 0;
  for (int i = 0; i < len_symbols; i++)
    freqs_symbols += 100 * frequency(text, (char)SYMBOLS[i]);

  int ratioNonPrintables = 100 * ratioNonPrintChars((uint8_t*)text, len);

  cout << endl;

  int hist_heigth = 15;
  int i = hist_heigth;
  while (i > 0) {
    // Print a single line
    printf(" | ");

    for (int j = 0; j < len_letters; j++) {
      if (freqs_letters[j] >= i)
        printf(" * ");
      else
        printf("   ");
    }

    // Separation with letters
    printf("    ");

    // for (int j = 0; j < len_letters; j++) {
    if (freqs_symbols >= i)
      printf(" * ");
    else
      printf("   ");
    //}

    printf("    ");

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

float indexOfCoincidence_(uint8_t* s, int len) {
  /** Returns the indexOfCoincidence over the Latin alphabet.
   *
   * Since encryption here is based on single-byte XOR, our alphabet is made of
   * 256 possibilities.
   */

  float sum = 0.;
  float I = 0.;
  float c = 26.;

  // Count only Latin chars out of the total length:
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

    // Sum occurrences of all letters.
    sum += n_i * (n_i - 1);
  }

  I = sum / (N * (N - 1));  //'* c;

  return I;
}

float indexOfCoincidence(uint8_t* s, int len) {
  /** Returns the indexOfCoincidence for a string over the "ASCII" alphabet.
   *
   * Since encryption here is based on single-byte XOR, our alphabet is made of
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

    // Sum occurrences of all letters.
    sum += n_i * (n_i - 1);
  }

  I = sum / (N * (N - 1));  //* c;

  return I;
}

float friedmanTest(uint8_t* s, int len) {
  // Reference index for ASCII alphabet computed from custom english texts.
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

int findKeyLength(uint8_t* ciphertext, int len) {
  int maxKeysize = 100;
  return findKeyLength(ciphertext, len, maxKeysize);
}

int findKeyLength(uint8_t* ciphertext, int len, int maxKeysize) {
  /** Find the length of the key of a ciphertext.
   *
   * Here we try to guess KEYSIZE. We test every values in a chosen range and
   * for each guessed KEYSIZE we reorganise the ciphertext into blocks of length
   * KEYSIZE. The new ciphertext looks now mono-alphabetically xor'ed. Then we
   * compute the index of coincidence Ic based on a 256 alphabet (ASCII) a
   * block, eg. the first one . The hightest Ic indicates you guessed the
   * correct key. Any hight values are going to be correspond to a multiple of
   * KEYSIZE. It works really well !
   */

  // int maxKeysize = 100;
  int l = len;

  for (int KEYSIZE = 2; KEYSIZE < maxKeysize; KEYSIZE++) {
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

    float I = indexOfCoincidence(blocks[1], p);
    if (I > 0.060) {
      //      cout << "KEYSIZE: " << KEYSIZE << " Ic = " << I << endl;
      return KEYSIZE;
    }
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
  //  uint8_t* ciphertext = (uint8_t*)read_text_file("resources/6_decoded.txt",
  //  &l);

  char* base64ed_encrypted_text =
      read_text_file("resources/6.txt", &l_ciphertext);
  //      uint8_t* ciphertext = base64Decode(base64ed_encrypted_text,
  //      l_ciphertext);
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
  singlebyteXORattackWithFrequencyScore(blocks[1], p, .5);

  // Test the reconstituted key.
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

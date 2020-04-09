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

int dict_size;
vector<string> dictionary;
map<string, int> map_dico;

void load_dictionary(const char* filename) {
  string resourcesdir = "./resources/";
  ifstream file;

  file.open(filename);

  try {
    file.open((resourcesdir + string(filename)).c_str());
    if (file.fail()) throw file.rdstate();

    for (std::string line; std::getline(file, line);) {
      // Get rid of the single letters in the file.
      if (line.length() != 1) {
        dictionary.push_back(line);
        map_dico[line] = 1;  // Just add the line in the keys for quick access.
      }
    }
    dict_size = dictionary.size();
  } catch (ios::iostate filestate) {
    if (filestate == ios::failbit) {
      cout << "failbit" << endl;
    }

    if (filestate == ios::badbit) {
      cout << "badbit" << endl;
    }
  }
}

int englishScore2(const char* sentence, int length) {
  int score = 0;

  // Locate a possible word in the sentence:
  int pos1 = 0;
  char c2;

  char* w;
  int i = 1;
  while (i < length) {
    c2 = sentence[i];

    if (c2 == ' ') {  //|| i== (length-1)
      int len_word = i - pos1;
      w = new char[len_word + 1];
      // w = (char*)malloc(sizeof(char)*(len_word+1));
      assert(w != NULL);
      strncpy(w, &sentence[pos1], len_word);
      w[len_word] = '\0';  // I don't like that...
      string word(w);

      pos1 = i + 1;
      i = pos1;

      if (map_dico.count(word) == 1) {
        score++;
        // cout << "word: " << word << endl;
      }
    }
    i++;
  }

  return score;
}

int englishScore(uint8_t* sentence) {
  string word;
  string sentence_string((char*)sentence);  // To use string::find
  int score = 0;

  int j = 0;
  while (j < (int)dictionary.size()) {
    word = dictionary[j];
    if (sentence_string.find(" " + word + " ") != string::npos) score++;

    j++;
  }

  if (score > 2)  // If the scoce is 0 we don't display anything.
  {
    // cout << endl;
    // cout << "Deciphered text:  " << endl;
    // cout << sentence << endl;
    // cout << "score: " << score << endl;
  }
  return score;
}

uint8_t singlebyteXORattack(uint8_t* ciphertext, int size, int thresold) {
  uint8_t* expandedKey = new uint8_t[size];
  uint8_t* deciphered;
  load_dictionary("google_10000_english.txt");
  assert(dictionary.empty() == false);

  int key = 0;
  int score = 0;
  int maxScore = 0;
  // char* plaintext;

  // Brut force attack of single-byte XOR
  for (int candidate_key = 0; candidate_key <= 0xFF; candidate_key++) {
    // Expand the key, cast the key to uint8_t to prevent infinite loop.
    memset(expandedKey, (uint8_t)candidate_key, size);

    deciphered = myXOR(ciphertext, expandedKey, size);
    score = englishScore2((char*)deciphered, size);

    // if (score > maxScore) {
    //   maxScore = score;
    //   key = candidate_key;
    //   plaintext = (char*)malloc (sizeof(char) * size);
    //   strncpy(plaintext,(char*)deciphered,size);
    // }

    // Display the plaintext
    if (score >= thresold) {
      cout << "score: " << score << endl;
      cout << "maxScore: " << maxScore << endl;
      cout << "Key:" << candidate_key << endl;
      printf("%s\n", deciphered);

      key = candidate_key;
    }
  }

  // Display the best score:
  // Display the plaintext
  // cout << "maxScore: " << maxScore << endl;
  // cout << "Key:" << key << endl;
  //  cout << plaintext << endl;
  // printf("%s\n", deciphered );

  delete[] expandedKey;

  return key;
}

void singlebyteXORattackWithFrequencyScore(uint8_t* ciphertext, int size) {
  uint8_t* key_array = new uint8_t[size];
  uint8_t* deciphered;
  load_dictionary("google_10000_english.txt");
  assert(dictionary.empty() == false);

  int score = 0;
  int maxScore = 0;

  // Brut force attack of single-byte XOR
  for (int candidate_key = 0; candidate_key <= 0xFF; candidate_key++) {
    // Expand the key
    memset(key_array, (uint8_t)candidate_key,
           size);  // Cast to uint8_t to prevent an infinite loop.

    deciphered = myXOR(ciphertext, key_array, size);
    // plot_frequencies(deciphered,size);
    // plot_frequencies((char*)deciphered);
    //    printf("%s\n", deciphered );

    score = englishScore2((char*)deciphered, size);
    if (score > maxScore) maxScore = score;

    // if (score > 2) {
    //   cout << "Score: " << score << endl;
    //   cout << "Key:" << key << endl;
    //   printf("%s\n", deciphered );
    //}
  }
}

void challenge_3() {
  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 1" << endl;
  cout << "3. Single-byte XOR cipher" << endl;
  cout << "------------------------------------\n" << endl;

  uint8_t toDecrypt[] = {0x1b, 0x37, 0x37, 0x33, 0x31, 0x36, 0x3f, 0x78, 0x15,
                         0x1b, 0x7f, 0x2b, 0x78, 0x34, 0x31, 0x33, 0x3d, 0x78,
                         0x39, 0x78, 0x28, 0x37, 0x2d, 0x36, 0x3c, 0x78, 0x37,
                         0x3e, 0x78, 0x3a, 0x39, 0x3b, 0x37, 0x36};

  int thresold = 3;
  int size = sizeof(toDecrypt);

  int key = singlebyteXORattack(toDecrypt, size, thresold);

  uint8_t* expandedKey = new uint8_t[size];
  memset(expandedKey, (uint8_t)key, size);
  // cout << myXOR(toDecrypt, expandedKey, size) << endl;

  delete[] expandedKey;
  // singlebyteXORattackWithFrequencyScore(toDecrypt, sizeof(toDecrypt));
}

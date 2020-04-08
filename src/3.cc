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
map<string,int> map_dico;

void load_dictionary(const char* filename) {
  string resourcesdir = "./resources/";
  ifstream file;

  file.open(filename);

  try {
    file.open((resourcesdir + string(filename)).c_str());
    if (file.fail()) throw file.rdstate();

    for (std::string line; std::getline(file, line);) {
      dictionary.push_back(line);
      map_dico[line] = 1; // Just add the line in the keys for quick access.
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
  uint8_t* word_candidate;

  // Locate a possible word in the sentence:
  int pos1=0;
  char c2 ;

  int i=1;
  while (i<length){
    c2 = sentence[i];

    if (c2 == ' ') {

      int len_word = i - pos1;
      char* word = (char*)malloc(sizeof(char)*(len_word+1));
      strncpy(word,sentence+pos1,len_word);
      pos1 = i+1;
      i = pos1;

      if (map_dico.count(word) == 1) {
        score++;
        cout << word << endl;
      }
    }
    i++;
  }

  return score;
}

int englishScore2(uint8_t* sentence, int length) {
  int score = 0;
  uint8_t* word_candidate;

  // Locate a possible word in the sentence:
  int l;
  int pos1=0;
  int pos2=0;
  char c1 = sentence[pos1];
  char c2 ;

  int i=1;
  while (i<length){
    c2 = (char)sentence[i];

    if (c2 == ' ') {
      l = (i-pos1);
//      word_candidate = (uint8_t*) malloc (sizeof(uint8_t) * (l) );
      word_candidate = (uint8_t*) realloc (word_candidate,l+1 );
      assert(word_candidate != NULL);
      //word_candidate[l+1] = NULL;

      memcpy(word_candidate,sentence,l);
      //memset(word_candidate+l,'\0',);
      printf("candidate: %s",word_candidate);
      string w((char*) word_candidate);
      //free(word_candidate);

      cout << w << endl;
      // Check if in the dictionary
      if (map_dico.count(w) == 1) {
        score++;
        cout << w << endl;
      }

      i++;
      pos1 = i+1;

//      break;
    }

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

void singlebyteXORattack(uint8_t* ciphertext, int size, int thresold) {
  uint8_t* key_array = new uint8_t[size];
  uint8_t* deciphered;
  load_dictionary("google_10000_english.txt");
  assert(dictionary.empty() == false);

  // Brut force attack of single-byte XOR
  for (int key = 0; key <= 0xFF; key++) {
    // Expand the key
    memset(key_array, (uint8_t)key,
           size);  // Cast to uint8_t to prevent an infinite loop.

    deciphered = myXOR(ciphertext, key_array, size);
    int score = englishScore(deciphered);
    if (score >= thresold) {
      cout << "Key:" << key << endl;
      printf("%s\n", deciphered );
    }
  }

  delete[] key_array;
}

void singlebyteXORattackWithFrequencyScore(uint8_t* ciphertext, int size) {
  uint8_t* key_array = new uint8_t[size];
  uint8_t* deciphered;
  load_dictionary("google_10000_english.txt");
  assert(dictionary.empty() == false);

  // Brut force attack of single-byte XOR
  for (int key = 0; key <= 0xFF; key++) {
    // Expand the key
    memset(key_array, (uint8_t)key,
           size);  // Cast to uint8_t to prevent an infinite loop.

    deciphered = myXOR(ciphertext, key_array, size);
    //plot_frequencies(deciphered,size);
    //plot_frequencies((char*)deciphered);
//    printf("%s\n", deciphered );

    int score = frequencyCheck((char*)deciphered);
    if (score > 2) {
      cout << "Score: " << score << endl;
      cout << "Key:" << key << endl;
      printf("%s\n", deciphered );
    }
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

  singlebyteXORattack(toDecrypt, sizeof(toDecrypt),3);
  //singlebyteXORattackWithFrequencyScore(toDecrypt, sizeof(toDecrypt));

}

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

#include "lib.h"

using namespace std;

int dict_size;
vector<string>
    dictionary;

void load_dictionary(const char* filename) {
  string resourcesdir = "./resources/";
  ifstream file;

  ios::iostate filestate;
  file.open(filename);

  try {
    file.open((resourcesdir + string(filename)).c_str());
    if (file.fail()) throw file.rdstate();

    int position = 0;
    for (std::string line; std::getline(file, line);) {
      dictionary.push_back(line);
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

void englishScore(uint8_t* sentence) {
  string word;
  string sentence_string((char*)sentence);  // To use string::find
  int score = 0;
  size_t not_found = string::npos;

  int j = 0;
  while (j < dictionary.size()) {
    word = dictionary[j];
    if (sentence_string.find(" " + word + " ") != string::npos) score++;

    j++;
  }

  if (score > 2)  // If the scoce is 0 we don't display anything.
  {
    cout << endl;
    cout << "Deciphered text:  " << endl;
    cout << sentence << endl;
    cout << "score: " << score << endl;
  }
}

void singlebyteXORattack(uint8_t* ciphertext, int size) {
  uint8_t* key_array = new uint8_t[size];
  uint8_t* deciphered;
  assert(dictionary.empty() == false);

  // Brut force
  for (int key = 0; key <= 0xFF; key++) {
    memset(key_array, (uint8_t)key,
           size);  // Cast to uint8_t to prevent an infinite loop.
    deciphered = myXOR(ciphertext, key_array, size);
    englishScore(deciphered);
  }
}

void challenge_3() {
  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 1" << endl;
  cout << "3. Single-byte XOR cipher" << endl;
  cout << "------------------------------------\n" << endl;

  uint8_t* c;
  uint8_t toDecrypt[] = {0x1b, 0x37, 0x37, 0x33, 0x31, 0x36, 0x3f, 0x78, 0x15,
                         0x1b, 0x7f, 0x2b, 0x78, 0x34, 0x31, 0x33, 0x3d, 0x78,
                         0x39, 0x78, 0x28, 0x37, 0x2d, 0x36, 0x3c, 0x78, 0x37,
                         0x3e, 0x78, 0x3a, 0x39, 0x3b, 0x37, 0x36};

  load_dictionary("google_10000_english.txt");
  singlebyteXORattack(toDecrypt, sizeof(toDecrypt));
}

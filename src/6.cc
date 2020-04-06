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

const char* readTextFile(const char* filename, int* length )
{
  /** Read a text file as well as the text length.
   * @param  filename A text file.
   * @return text     The text in the file.
   * @return length   The length of the read text.
   */

  ios::iostate filestate;
  ifstream file;
  char* out;

  try {
    file.open(filename);

    if (file.fail()) throw file.rdstate();

    // get length of file:
    file.seekg (0, file.end);
    *length = file.tellg();
    file.seekg (0, file.beg);

    out = (char*) malloc (sizeof(char) * (*length));
    file.read(out,*length);
  }
  catch (ios::iostate filestate) {
    if (filestate == ios::failbit) {
      cout << "failbit" << endl;
    }

    if (filestate == ios::badbit) {
      cout << "badbit" << endl;
    }
  }
  return out;
}

const char* readTextFile(const char* filename)
{
  /** Read a text file and discard the text length. */
  int length;
  return readTextFile(filename, &length );
}

int hammingDistance(const char* a, const char* b) {
  assert(strlen(a) == strlen(b));
  uint8_t byte;
  int distance = 0;

  for (int i = 0; i < strlen(a); i++) {
    byte = a[i] ^ b[i];

    int j = 0;
    while (j < 8) {
      distance += (byte >> j) & 1;
      j++;
    }
  }
  return distance;
}

void TestHammingDistance()
{
  string a = "this is a test";
  string b = "wokka wokka!!!";
  cout << hammingDistance(a.c_str() , b.c_str()) << endl;
}

int occurence(const char* s, char myChar )
{
    int occ = 0;
    char current = s[0];
    int i=0;
    while (current != '\0')
    {
        if (current == myChar)
            occ++;
        current = s[i+1];
        i++;
    }
    return occ;
}

float frequency(const char* s,char c)
{
    if (occurence(s,c) == 0) {
        return 0;
    }
    else {
        return  ( (float) occurence(s,c) / (float) strlen(s) );
    }
}

float frequencyCheck(const char* s)
{
    string sentence(s); // to use the find function.

    int deltas[8]; // Store deltas of the 8th most frequent letters in english.

    deltas[0] = frequency(s,'e') - 12.02;
    deltas[1] = frequency(s,'t') - 9.10;
    deltas[2] = frequency(s,'a') - 8.12;
    deltas[3] = frequency(s,'o') - 7.68;
    deltas[4] = frequency(s,'i') - 7.31;
    deltas[5] = frequency(s,'n') - 6.95;
    deltas[6] = frequency(s,'s') - 6.28;
    deltas[7] = frequency(s,'r') - 6.02;

    int sum = 0;
    for (int i=0;i<8;i++)
        sum += deltas[i];

    return sum;
}

void plot_frequencies(const char* text)
{
  /** Plot frequencies for the first 5 letters. */
  int f1=2*100*frequency(text,'e');
  int f2=2*100*frequency(text,'t');
  int f3=2*100*frequency(text,'a');
  int f4=2*100*frequency(text,'o');
  int f5=2*100*frequency(text,'i');
  int f6=2*100*frequency(text,'n');

  cout << "e " ;
  for (int i=0;i<f1;i++)
    cout << "-";
  cout << endl;

  cout << "t "  ;
  for (int i=0;i<f2;i++)
    cout << "-";
  cout << endl;

  cout << "a " ;
  for (int i=0;i<f3;i++)
    cout << "-";
  cout << endl;

  cout << "o " ;
  for (int i=0;i<f4;i++)
    cout << "-";
  cout << endl;

  cout << "i " ;
  for (int i=0;i<f5;i++)
    cout << "-";
  cout << endl;

  cout << "n " ;
  for (int i=0;i<f6;i++)
    cout << "-";
  cout << endl;
}

void challenge_6() {
  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 1" << endl;
  cout << "6. Break repeating-key XOR" << endl;
  cout << "------------------------------------\n" << endl;

  TestHammingDistance();
  //const char* base64ed_encrypted_text = readTextFile("resources/6.txt");
  //char* encrypted_text = base64Decode();

  // 1)
  // int limit = 40;
  // for (int KEYSIZE=0;i<=limit;i++)
  //     {
  //
  //     }

  //test zone
  int length;
  const char* text = readTextFile("resources/dummy_text.txt",&length);
  cout << frequency(text,'e')  << endl;
 plot_frequencies(text);
}

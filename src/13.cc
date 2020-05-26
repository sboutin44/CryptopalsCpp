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

void printJsonStyle(map<string, string> m) {
  cout << "{" << endl;
  for (auto it = m.begin(); it != m.end(); it++) {
    cout << "  " << it->first << ": "
         << "'" << it->second << "'"
         << "," << endl;
  }
  cout << "}" << endl;
  cout << endl;
}

map<string, string> parse(string s) {
  map<string, string> json;
  int pos0 = 0;
  int pos1 = 0;
  int pos2 = 0;

  while (pos2 < s.length()) {
    // Find the first =
    pos1 = s.find('=');
    pos2 = s.find('&');
    string key = s.substr(pos0, pos1 - pos0);
    string val = s.substr(pos1 + 1, pos2 - (pos1 + 1));

    json[key] = val;

    // Set next position and redefine the substring we work on.
    pos0 = pos2 + 1;
    s = s.substr(pos0, s.length());
  }
  return json;
}

void challenge_13() {
  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 2" << endl;
  cout << "13. ECB cut-and-paste" << endl;
  cout << "------------------------------------\n" << endl;

  map<string, string> m;
  string s = "foo=bar&baz=qux&zap=zazzle";
  m = parse(s);

  printJsonStyle(m);
}

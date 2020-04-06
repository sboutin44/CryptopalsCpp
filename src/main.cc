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

void run_challenge(int selection) {
  switch (selection) {
    case 1:
      challenge_1();
      break;
    case 2:
      challenge_2();
      break;
    case 3:
      challenge_3();
      break;
    case 4:
      challenge_4();
      break;
    case 5:
      challenge_5();
      break;
    case 6:
      challenge_6();
      break;
    default:
      std::cerr << "Selection =" << unsigned(selection) << std::endl;
      break;
  }
}

int main(int argc, char* argv[]) {
  int selection = 0;

  if (argc == 2) {
    selection = std::stoi(argv[1]);
    run_challenge(selection);
    return 0;
  }

  else {
    std::cerr << "\nUsage: \n\t"
              << "cryptopals"
              << " #challenge" << std::endl;
    // std::cerr << "To launch the challenge Set 1 - 1.Convert hex to base64:"
    // << std::endl;
    std::cerr << "\nExample:";
    std::cerr << "\n\tcryptopals"
              << " 1" << std::endl;
    std::cerr << "\t=> launch Set 1 - 1.Convert hex to base64" << std::endl;

    std::cerr << "\n\tcryptopals"
              << " 9" << std::endl;
    std::cerr << "\t=> launch Set 2 - 9.Implement PKCS#7 padding" << std::endl;
    std::cerr << std::endl;
    return 1;
  }
}

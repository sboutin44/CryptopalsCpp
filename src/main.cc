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

#include "aes.h"
#include "lib.h"
#include "tests.h"
#include "tests_aes.h"

using namespace std;

void runChallenge(int challenge) {
  switch (challenge) {
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
    case 7:
      challenge_7();
      break;
    case 8:
      challenge_8();
      break;
    case 9:
      challenge_9();
      break;
    case 10:
      challenge_10();
      break;
    case 11:
      challenge_11();
      break;
    case 12:
      challenge_12();
      break;

      // see cryptopalsPython for challenges in between 13 to 18.

    case 18:
      challenge_18();
      break;
    case 19:
        challenge_19();
        break;

    default:
      std::cerr << "Challenge " << unsigned(challenge) << " not solved yet!"
                << std::endl;
      break;
  }
}

void runTests() {
  testCountLines();
  testBase64Encode();
  testBase64Decode();
  testHammingDistance();
  testInsertionSort();
  testHistogram();
  testFindKeyLength();
  testAES128();
  testGuessEncryptionMode();
  testDetectBlockSize();
  testGuessEncryptionMode();
}

void displayProgramUsage() {
  std::cerr << "\nUsage: ";
  std::cerr << "\n\tcryptopals --challenge #challenge\n";

  std::cerr << "\nExample:";
  std::cerr << "\n\tcryptopals --challenge 1\n";
  std::cerr << "\t=> launch Set 1 - 1.Convert hex to base64\n";
  std::cerr << "\n\tcryptopals --challenge 9\n";
  std::cerr << "\t=> launch Set 2 - 9.Implement PKCS#7 padding\n";

  std::cerr << "\nReseved for development purposes:\n\n";
  std::cerr << "\tcryptopals --run_tests" << std::endl;
  std::cerr << "\tcryptopals --quick_test" << std::endl;

  std::cerr << std::endl;
}

void testFunction() {}

int main(int argc, char *argv[]) {
  /** The program can be run in two modes.
   *
   * Normal:
   *    ./cryptopals {#challenge}
   *
   * Test:
   *  Only used for development purpose:
   *    ./cryptopals --run_tests
   * will launch the function called in testFunction().
   */

  if (argc == 2) {
    if (std::string(argv[1]) == "--help") {
      displayProgramUsage();
    } else if (std::string(argv[1]) == "--run_tests") {
      runTests();
    } else if (std::string(argv[1]) == "--quick_test") {
      testFunction();
    } else {
      std::cerr << "\nError: \t"
                << " unknown argument: '" << std::string(argv[1]) << "'\n";
      displayProgramUsage();
    }
  }

  else if (argc == 3) {
    if (std::string(argv[1]) == "--challenge") {
      int challenge = std::stoi(argv[2]);
      runChallenge(challenge);
      return 0;
    }
  } else {
    displayProgramUsage();
    return 1;
  }
}

// Copyright © 2020 Sebastien BOUTIN
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// Except as contained in this notice, the name(s) of the above copyright holders
// shall not be used in advertising or otherwise to promote the sale, use or other
// dealings in this Software without prior written authorization.

#include "lib.h"
using namespace std;

void challenge_4()
{
    cout << "\n============================" << endl;
    cout << "Set 1   Challenge 4" << endl;

    string resourcesdir = "./resources/";
    string filename = "ciphertext_set1_chall4.txt";

    load_dictionary("google_10000_english.txt");


    ios::iostate filestate;
    ifstream fileToDecrypt;

    try {
        fileToDecrypt.open((resourcesdir+filename).c_str());

    //    if ( (fileToDecrypt.rdstate() & std::ifstream::failbit ) != 0 ) {
        if ( fileToDecrypt.fail() )
            throw fileToDecrypt.rdstate();

        uint8_t* hexline = new uint8_t[60];
        for (std::string line; std::getline(fileToDecrypt, line) ; )
        {
            hexDecode(line.c_str(),hexline);
            singlebyteXORattack(hexline,60);
        }
    }
    catch (ios::iostate filestate)
    {
        if (filestate == ios::failbit) {
            cout << "failbit" << endl;
        }

        if (filestate == ios::badbit) {
            cout << "badbit" << endl;
        }
    }
}

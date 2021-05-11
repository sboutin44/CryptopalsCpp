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



void challenge_19() {
    // 

    string resourcesdir = "./resources/";
    string filename = "19.txt";
    ifstream file;
    vector<bytearray_t*> ciphers;

    file.open(filename);

    byte* key = new byte[16];  // Allocate a default AES128 key.
    randomAES128key(key);

    try {
        file.open((resourcesdir + string(filename)).c_str());
        if (file.fail()) throw file.rdstate();

        int nb_lines = 0;
        for (std::string line; std::getline(file, line);) {
            nb_lines++;
            
            // Base64 decode
            bytearray_t* decoded = new bytearray_t();
            decoded->l = getDecodedTextSize((uint8_t*)line.c_str(), line.size());
            decoded->data_ptr = new byte[decoded->l];
            base64Decode((uint8_t*)line.c_str(), decoded->l, decoded->data_ptr);
            
            // Encrypt 
            bytearray_t* c;
            c= AES_CTR_enc(decoded, key);

            ciphers.push_back(c);
        }
    }

    catch (ios::iostate filestate) {
        if (filestate == ios::failbit) {
            cout << "failbit" << endl;
        }
        
        if (filestate == ios::badbit) {
            cout << "badbit" << endl;
        }
    }
    
}


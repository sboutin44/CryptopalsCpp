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

 #include <iostream>
 #include <string>
 #include <sstream>
 #include <cstring>
 #include <cstdlib>
 #include <cassert>
 #include "lib.h"
 using namespace std;


 void repeatedKeyXor (const char* input, const char* key, char* output)
 {
     int inputSize = strlen(input);
     int keySize = strlen(key);

     for (int i=0 ; i<inputSize ; i++){
         output[i] = input[i] ^ key[i%keySize];
     }
 }

 void challenge_5()
 {
     const char* a = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
     const char* key = "ICE";
     char* output;

     output = new char[strlen(a)];
     repeatedKeyXor(a,key,output);
     for (int i=0;i<strlen(a);i++)
         printf("%02x",output[i]);
     delete[] output;
 }

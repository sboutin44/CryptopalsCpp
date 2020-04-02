/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
 // Example program
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

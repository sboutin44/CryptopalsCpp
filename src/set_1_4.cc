/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <iostream>
#include <string>
#include <cassert>
#include <cstring>
#include <fstream>
#include "lib.h"
using namespace std;

void hexDecode(const char* input, uint8_t* out )
{
    std::string myString(input);

    for (int i=0;i<strlen(input);i+=2) {
        std::string substr = myString.substr(i,2);
        out[i] = strtoul(substr.c_str(), 0, 16);
    }
}

int main()
{
    cout << "\n============================" << endl;
    cout << "Set 1   Challenge 4" << endl;

    string resourcesdir = "resources/";
    string filename = "ciphertext_set1_chall4.txt";

    ifstream fileToDecrypt;
    fileToDecrypt.open((resourcesdir+filename).c_str());

    if ( (fileToDecrypt.rdstate() & std::ifstream::failbit ) != 0 ) {
        std::cerr << "Error opening " << filename << "\n";
        return 1;
    }

    uint8_t* hexline = new uint8_t[60];
    for (std::string line; std::getline(fileToDecrypt, line) ; )
    {
        hexDecode(line.c_str(),hexline);
        singlebyteXORattack(hexline,60);
    }

}
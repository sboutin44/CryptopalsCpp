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

int main()
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
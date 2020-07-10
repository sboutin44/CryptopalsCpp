#include <iostream>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <sstream>
#include <iomanip>
#include "c01.hxx"

using namespace std;


int main()
{
    
   string input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
   uint8_t* output;
   string_to_hex(input, output);
}
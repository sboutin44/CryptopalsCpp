#include <iostream>
#include "c01.hxx"

using namespace std;


int main()
{
    
   string input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
   uint8_t* output;
   int n;
   string_to_hex(input, output, n);
   
   for(int i = 0; i < n; i++)
        printf("%x", output[i]);
   printf("\n");
   cout << input << endl;

   string output2;
   hex_to_string(output, n, output2);
   cout << output2 << endl;
}
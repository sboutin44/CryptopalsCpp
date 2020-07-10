#include <iostream>
#include <cstring>
#include <cstdint>
#include <cassert>
#include <sstream>
#include <iomanip>

using namespace std;

void string_to_hex(const string& input, uint8_t* output)
{
    /** Convert a string of hexadecimal to its memory hexadecimal representation
    * @param input sting of hexadecimal number
    * @param output array of hexadecimal representation of input
    */
    size_t lenInput = input.size();
    assert(lenInput%2 == 0); // The length of hex should be pair.
    output = new uint8_t[lenInput/2];

    // Letter used in the hex representation of numbers
    string hexChars = "AaBbCcDdEeFf";

    // Used to check that two char are convert in one input (one octet) in the output array.
    int is_pair = 0;
    // Index of output's array.
    int i = 0;

    for(char c : input)
    {
        if(!is_pair)
        {
            output[i] = (hexChars.find_first_of(c) != string::npos) ? (((c - 'a') + 10) << 4) : ((c - '0') << 4);
            is_pair = 1;
        }
        else
        {
            output[i] ^= (hexChars.find_first_of(c)!= string::npos) ? ((c - 'a') + 10) : (c - '0');
            is_pair = 0;
            i++;
        }
    }

    for(int i = 0; i < lenInput/2; i++)
        printf("%x", output[i]);
    printf("\n");
}

void hex_to_string(const uint8_t* input, string output)
{
    size_t lenInput = sizeof(input)/sizeof(*input);

    stringstream ss;

    cout << "longueur input = " << lenInput << endl;
    cout << "input[0] = " << input[0] << endl;

    for (int i = 0; i < lenInput; i++)
    {
        ss << input[i];
    }
    cout << "output =" << output << endl;
    output = ss.str();
    ss.clear();    
}

int main()
{
    
   string input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
   uint8_t* output;
   string_to_hex(input, output);
   
   string output2;
   hex_to_string(output, output2);
   cout << output2 << endl;

}
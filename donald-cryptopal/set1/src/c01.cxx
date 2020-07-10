#include "c01.hxx"

void string_to_hex(const std::string& input, uint8_t* output)
{
    /** Convert a string of hexadecimal to its memory hexadecimal representation
    * @param input sting of hexadecimal number
    * @param output array of hexadecimal representation of input
    */
    size_t lenInput = input.size();
    assert(lenInput%2 == 0); // The length of hex should be pair.
    output = new uint8_t[lenInput/2];

    // Letter used in the hex representation of numbers
    std::string hexChars = "AaBbCcDdEeFf";

    // Used to check that two char are convert in one input (one octet) in the output array.
    int is_pair = 0;
    // Index of output's array.
    int i = 0;

    for(char c : input)
    {
        if(!is_pair) // Fill four left bits of output[i]
        {
            output[i] = (hexChars.find_first_of(c) != std::string::npos) ? (((c - 'a') + 10) << 4) : ((c - '0') << 4);
            is_pair = 1;
        }
        else// Fill four right bits of output[i]
        {
            output[i] ^= (hexChars.find_first_of(c)!= std::string::npos) ? ((c - 'a') + 10) : (c - '0');
            is_pair = 0;
            i++;
        }
    }

    for(int i = 0; i < lenInput/2; i++)
        printf("%x", output[i]);
    printf("\n");
}

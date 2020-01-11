//============================================================================
// Name        : Matasano.cpp
// Author      : Sebastien Boutin
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <iostream>
#include <string>
using namespace std;

char Base64_table[] =
{
    'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
    '0','1','2','3','4','5','6','7','8','+','/'
};

char* base64Encode(const char* input, int size) {
    /** Encode an input made of raw bytes in base64.
     *
     * @param input String input treated as raw bytes.
     * @param size String size.
     *
     * Note on the masks used:
     *
     * 0xFC
     * 0x03
     * 0xF0
     * 0x0F
     * 0xC0
     * 0x3F
     */
    uint8_t a, b, c, d, e, f,g;
    int output_length = (size / 3) * 4 + 4; // Every 3 letters, 4 letters are created, plus the 4 last ones.
    char* output = new char[output_length];

    // Treat the 3-tuples.
    int output_position = 0; // track the position in the output array.
    for (int i = 0; i < (size / 3); i+=3)
    {
        a = (input[i] & 0xFC) >> 2;
        b = (input[i] & 0x03) << 4 ^ (input[i + 1] & 0xF0) >> 4;
        c = (input[i + 1] & 0x0F) << 2 ^ (input[i + 2] & 0xC0) >> 6;
        d = (input[i + 2] & 0x3F);

        output[output_position] = Base64_table[a];
        output[++output_position] = Base64_table[b];
        output[++output_position] = Base64_table[c];
        output[++output_position] = Base64_table[d];
    }

    // Treat the end of the string when 2 characters remain.
    if (size % 3 == 2) {
        e = (input[size - 2] & 0xFC) >> 2;
        f = (input[size - 2] & 0x03) << 4 ^ (input[size - 1] & 0xF0) >> 4;
        g = (input[size - 1] & 0x0F) << 2;

        output[output_position] = Base64_table[e];
        output[++output_position] = Base64_table[f];
        output[++output_position] = Base64_table[g];
        output[++output_position] = '=';
    }

    // Treat the end when 1 character remain.
    if (size % 3 == 1) {
        e = (input[size - 2] & 0xFC) >> 2;
        f = (input[size - 2] & 0x03) << 4;

        output[output_position] = Base64_table[e];
        output[++output_position] = Base64_table[f];
        output[++output_position] = '=';
        output[++output_position] = '=';
    }

    return output;
}

int getLength(const char* s)
{
    char c = s[0];
    int count = 0;
    while (c != '\0') {
        count++;
        c = s[count];
    }
    return count;
}


int main() {

    // Sources of the inputs:
    // https://en.wikipedia.org/wiki/Base64

    const char* sebastien = "Sebastien";
    const char* test_string = "any carnal pleasure.";

    int size = getLength(sebastien);
    assert(size == 9);

    size = getLength(test_string);
    cout << size << endl;
    char* res = base64Encode(test_string,size);

    cout << res ;

    return 0;
}

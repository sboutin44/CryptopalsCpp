#include "c03.hxx"
#include "test_c03.hxx"

bool test_single_byte_xor_cipher()
{
    std::string input = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    std::string output;
    uint8_t key;
    single_byte_xor_cipher(input, key, output);
    return true;
}
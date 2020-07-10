#ifndef __C01_HXX__
#define __C01_HXX__

#include "lib.hxx"

void string_to_hex(const std::string& input, uint8_t* output);
void hex_to_string(const uint8_t* input, std::string output);

void hex_to_base64(const uint8_t* input, base64 output);
#endif//__C01_HXX__

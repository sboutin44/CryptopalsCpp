
#ifndef BASE64_HPP_
#define BASE64_HPP_


char* base64Encode(const char* input, int size);
uint8_t* base64Decode(const char* input, int size);
uint8_t* myXOR(uint8_t* a, uint8_t* b, int size);
int test_base64();

#endif //BASE64_HPP_

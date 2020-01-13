
#ifndef BASE64_HPP_
#define _BASE64_HPP_


char* base64Encode(const char* input, int size);
uint8_t* base64Decode(const char* input, int size);
uint8_t* myXOR(uint8_t* a, uint8_t* b, int size);


#endif //_BASE64_HPP_

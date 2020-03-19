
#ifndef CRYPTOPALS_INC_LIB_H_
#define CRYPTOPALS_INC_LIB_H_

#include <vector>

char* base64Encode(const char* input, int size);
uint8_t* base64Decode(const char* input, int size);
uint8_t* myXOR(uint8_t* a, uint8_t* b, int size);
int test_base64();

// Defined in set_1_3_lib
void load_dictionary(const char* filename);
void quickEnglishChecker(uint8_t* sentence);
void singlebyteXORattack(uint8_t* ciphertext, int size );
void singlebyteXORattack2(uint8_t* ciphertext, int size );

// Set_1_3 Set_1_4 Set_1_5
void hexDecode(const char* input, uint8_t* out);
void singlebyteXORattack(uint8_t* ciphertext, int size );

#endif //CRYPTOPALS_INC_LIB_H_

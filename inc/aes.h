#ifndef CRYPTOPALS_INC_AES_H_
#define CRYPTOPALS_INC_AES_H_

void expandKey();

void addRoundKey();
void shiftRows();
void mixColumns();
void subBytes();

void invAddRoundKey();
void invShiftRows();
void invMixColumns();
void invSubBytes();


#endif //CRYPTOPALS_INC_AES_H_

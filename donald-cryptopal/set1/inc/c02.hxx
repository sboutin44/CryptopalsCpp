#ifndef __C02_HXX__
#define __C02_HXX__

#include "lib.hxx"
#include "c01.hxx"

/** @brief  Get two equal-length bytes array in input and computes the XOR of them.
 *  @param  input0      first input bytes array
 *  @param  lenInput0   length of input0
 *  @param  input1      second input bytes array
 *  @param  lenInput1   length of input1
 *  @param  lenOutput   length of output
 *  @param  output      bytes array which get the result of XOR of input0 and input1
 */
void bytes_array_fixed_xor(const uint8_t* input0, const int lenInput0, 
    const uint8_t* input1, const int lenInput1, int &lenOutput, uint8_t* &output);

/** @brief  Takes two hex encoded strings and compute their XOR
 *  @param  inputStr0   first hex encoded string
 *  @param  inputStr1   second hex encoded string
 *  @param  outputStr   hex encoded string which contains the XOR of two input strings.
 */
void fixed_xor(const std::string &inputStr0, const std::string &inputStr1, std::string &outputStr);

#endif /* __C02_HXX__*/
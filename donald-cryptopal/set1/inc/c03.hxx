#ifndef __C03_HXX__
#define __C03_HXX__

#include "lib.hxx"
#include "c01.hxx"

/** @brief  Decode a bytes array where each byte is xor'd with byte key.
 *  @param  input       Encrypted input array of bytes.
 *  @param  lenInput    Length of input array.
 *  @param  key         Decryption key.
 *  @param  lenOutput   Length of output array.
 *  @param  output      Decrypted array of bytes.
 */
void decode_bytes(const uint8_t* input, const int lenInput, \
        const uint8_t key, int &lenOutput, uint8_t* &output);

/** @brief  Check if a string is printable.
 *  @param  inputStr    String that we want to know if it is printable.
 */
bool isPrintable(const std::string inputStr);

/** @brief  Compute the score of input string, using norm L1 between letter in string and english letter frequency 
 *  @param  input       String that we want to compute score.
 *  @param  score       Score attribued to input string.
 */
void compute_string_score(const std::string input, float& score);

/** @brief  Take a hex encoded string which is xor'd encrypted with an unknow key and return a decryption of input and de encryption key. 
 *  @param  inputStr    Encrypted hex encoded string with an unknow key.
 *  @param  key         Key which encrypt input and that we looking for.
 *  @param  outputStr   Decryption of input key.
 */
void single_byte_xor_cipher(const std::string inputStr, uint8_t &key, std::string &outputStr);

#endif /* __C03_HXX__*/
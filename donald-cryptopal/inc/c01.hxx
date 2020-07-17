#ifndef __C01_HXX__
#define __C01_HXX__

#include "lib.hxx"

/** Encode string with hexa chars to array of bytes that corresponds to that hexa values.
 * @param   input       String with hexa chars.
 * @param   lenOutput   Length of output array.
 * @param   output      Array of bytes that corresponds to hexa input values.
 */
void hex_string_to_hex_array(const std::string &input, int& lenOutput, uint8_t* &output);

/** Encode a bytes' array into a string where char is hex representation of byte.
 * @param   input       Array of bytes.
 * @param   lenInput    Length of input array.
 * @param   output      String where chars are hex representation of number from input array.      
 */
void hex_array_to_hex_string(const uint8_t* input, const int lenInput, std::string &output);

/** Convert an array of bytes to its base64 representation array.
 * @param   input       Array of bytes.
 * @param   lenInput    Length of input array.
 * @param   output      Array which corresponds to base64 representation of input array.
 */
void hex_array_to_base64(const uint8_t* input, const int lenInput, base64& output);

/** Make inverse of hex_to_base64
 * @param   input       Array of base64 encoding.
 * @param   lenOutput   Length of output array.
 * @param   output      Array of bytes which contains decoding values from input.
 */
void base64_to_hex_array(const base64 &input, int& lenOutput, uint8_t* &output);

/** Convert any string to its base64 string representation.
 * @param   input       String to convert in base64
 * @param   output      String that represente the base64 encoding of input.
 */
void string_to_base64(const std::string &input, base64 &output);

/** Convert a base64 string into usual representation of string.
 * @param   input       Base64 string.
 * @param   output      Usual representation of string.
 */
void base64_to_string(const base64 &input, std::string &output);

#endif//__C01_HXX__

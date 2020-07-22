#include "c01.hxx"


void string_to_bytes(const std::string inputStr, int &lenOuput, uint8_t* &output)
{
    /** Convert a string into array of byte
     * @param   inputStr       input string
     * @param   lenOuput    length of output array of byte
     * @param   output      array of byte
     */
    lenOuput = inputStr.size();
    output = new uint8_t[lenOuput];
    int i = 0;
    for (char c : inputStr)
    {
        output[i] = c;
        i++;
    }
}

void bytes_to_string(const uint8_t* input, const int lenInput, std::string &outputStr)
{
/** @brief  Convert a array of byte to its string representation.
 *  @param  input       input bytes array
 *  @param  lenInput    length of input array
 *  @param  outputStr   string which representes input array.
 */
    outputStr.assign(input, input + lenInput);
}

void hex_string_to_hex_array(const std::string &input, int& lenOutput, uint8_t* &output)
{
    /** Encode string with hexa chars to array of bytes that corresponds to that hexa values.
     * @param   input       String with hexa chars.
     * @param   lenOutput   Length of output array.
     * @param   output      Array of bytes that corresponds to hexa input values.
     */


    /* The length of hex string should be even */
    assert((input.size() % 2) == 0);

    lenOutput = input.size()/2;
    output = new uint8_t[lenOutput];

    for (int i = 0; i < lenOutput; i++)
    {
        output[i] = std::strtol(input.substr(2*i, 2).c_str(), NULL, 16);
    }
}

void hex_array_to_hex_string(const uint8_t* input, const int lenInput, std::string &output)
{
    /** Encode a bytes' array into a string where char is hex representation of byte.
     * @param   input       Array of bytes.
     * @param   lenInput    Length of input array.
     * @param   output      String where chars are hex representation of number from input array.      
     */

    std::ostringstream ss;

    for (int i = 0; i < lenInput; i++)
    {
        ss <<  std::hex << std::setfill('0') << std::setw(2) << (int)input[i];
    }
    output = ss.str();
    ss.clear();    
}

void base64_padding(const uint8_t* input, const int lenInput, std::string& output)
{
    /** Pad the last four characters for base64 representation.
     * @param   input       Array of last byte of hex string.
     * @param   lenInput    The number of column (byte) in the input.
     * @param   output      Base64 representation of four last characters ending with '=' or "==". 
     */
    uint8_t b0, b1, b2;
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    switch (lenInput%3)
    {
        /* If input has just one byte base64 representation ends with two '=' */
        case 1 :            
            b0 = (input[lenInput - 1] >> 2) & 0b00111111;
            b1 = ((input[lenInput - 1] & 0b00000011) << 4) & 0b00110000;
            
            output += alphabet[b0];
            output += alphabet[b1];
            output += "=";
            output += "=";
            break;
        /* If input has two bytes base64 representation ends with one '=' */
        case 2 :
            b0 = (input[lenInput - 2] >> 2) & 0b00111111;
            b1 = ((input[lenInput - 2] & 0b00000011) << 4) ^ ((input[lenInput - 1] >> 4) & 0b00001111);
            b2 = ((input[lenInput - 1] & 0b00001111) << 2) & 0b00111100;

            output += alphabet[b0];
            output += alphabet[b1];
            output += alphabet[b2];
            output += "=";
            break;
        default:
            break;
    }
}

void convert_to_base64(const uint8_t* input, std::string& output)
{
    /** Convert three bytes into four base64 characters.
     * @param   intput      Three input bytes.
     * @param   output      Four output base64 characters. 
     */
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    uint8_t b0, b1, b2, b3;
    b0 = (input[0] >>2) & 0b00111111;
    b1 = ((input[0] & 0b00000011) << 4) ^ ((input[1] >> 4) & 0b00001111);
    b2 = ((input[1] & 0b00001111) << 2) ^ ((input[2] >> 6) & 0b00000011);
    b3 = input[2] & 0b00111111;
    
    output += alphabet[b0];
    output += alphabet[b1];
    output += alphabet[b2];
    output += alphabet[b3];
}

void hex_array_to_base64(const uint8_t* input, const int lenInput, base64& output)
{
    /** Convert an array of bytes to its base64 representation array.
     * @param   input       Array of bytes.
     * @param   lenInput    Length of input array.
     * @param   output      Array which corresponds to base64 representation of input array.
     */
    
    int regularLen; //length without last bytes to pad.
    regularLen = lenInput - (lenInput % 3);

    for (int i = 0; i < regularLen; i += 3)
        convert_to_base64(input + i, output);

    base64_padding(input, lenInput, output);
}

void inv_convert_to_base64(const std::string &input, const int posInInput, const int posInOutput, uint8_t* &output)
{
    /** Inverse function of convert_to_base64: convert four base64 characters to three bytes.
     * @param   input       String which contains four base64 characters to convert.
     * @param   posInInput  Position of cursor in the input string.
     * @param   posInOutput Position of cursor in the output array.
     * @param   output      Array which collect three bytes converted.
     */

    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    uint8_t b0, b1, b2, b3;

    /* Get index of input chars in base64 alphabet */
    b0 = (uint8_t)alphabet.find(input[posInInput+0]);
    b1 = (uint8_t)alphabet.find(input[posInInput+1]);
    b2 = (uint8_t)alphabet.find(input[posInInput+2]);
    b3 = (uint8_t)alphabet.find(input[posInInput+3]);

    output[posInOutput+0] = ((b0 & 0b00111111) << 2) ^ ((b1 >> 4) & 0b00000011);
    output[posInOutput+1] = ((b1 & 0b00001111) << 4) ^ ((b2 >> 2) & 0b00001111);
    output[posInOutput+2] = ((b2 << 6) & 0b11000000) ^ (b3 & 0b00111111);
}

void get_len_padding(const base64 &input, int &lenPad)
{
    /** Give length of padding in input base64 representation.
     * @param   input       Base64 string.
     * @param   lenPad      Length of padding which is number of char '=' in the end of input.
     */

    lenPad = 0;
    int n = input.size();

    if (input[n-1] == '=')
    {
        lenPad++;
        if (input[n-2] == '=')
            lenPad++;        
    }
    
    
}

void base64_unpadding(const base64 &input, const int posInOutput, uint8_t* &output)
{
    /** Construct the last bytes of array by removing padding from base64 representation.
     * @param   input       Base64 string where we are interested by four last characters.
     * @param   posInOutput Position of cursor in the output array.
     * @param   output      Array which collect bytes converted from last four character of input.  
     */

    int n = input.size();
    uint8_t b0, b1, b2;
    std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    /* Get index of input char in base64 alphabet */
    b0 = (uint8_t)alphabet.find(input[n-4]);
    b1 = (uint8_t)alphabet.find(input[n-3]);


    if (input[n-1] == '=')
    {
        if (input[n-2] == '=')
        {
            output[posInOutput] = ((b0 & 0b00111111) << 2) ^ ((b1 & 0b00110000) >> 4);
        }
        else
        {
            b2 = (uint8_t)alphabet.find(input[n-2]);
            output[posInOutput] = ((b0 & 0b00111111) << 2) ^ ((b1 & 0b00110000) >> 4);
            output[posInOutput+1] = ((b1 & 0b00001111) << 4) ^ ((b2 &0b00111100) >> 2);   
        }
        
        
    }
    
}

void base64_to_hex_array(const base64 &input, int& lenOutput, uint8_t* &output)
{
    /** Make inverse of hex_to_base64
     * @param   input       Array of base64 encoding.
     * @param   lenOutput   Length of output array.
     * @param   output      Array of bytes which contains decoding values from input.
     */

    int regularLen = input.size();
    int n = regularLen;
    
    // One base64 string which ends with "=" is a string that was padded.
    if (input[n-1] == '=')
        regularLen -= 4;

    int lenPad;
    get_len_padding(input, lenPad);

    /* Compute the length of output from that of base64 string */
    lenOutput = (regularLen/4)*3 + ((3-lenPad)%3);
    output = new uint8_t[lenOutput];

    int posInOuput = 0;
    for (int posInInput = 0; posInInput < regularLen; posInInput += 4, posInOuput +=3)
    {
        inv_convert_to_base64(input, posInInput, posInOuput, output);
    }

    base64_unpadding(input, posInOuput, output);        
}

void string_to_base64(const std::string &input, base64 &output)
{
    /** Convert any string to its base64 string representation.
     * @param   input       String to convert in base64
     * @param   output      String that represente the base64 encoding of input.
     */

    uint8_t *arrayBytesOfInput;
    int lenArrayByte;

    string_to_bytes(input, lenArrayByte, arrayBytesOfInput);
    hex_array_to_base64(arrayBytesOfInput, lenArrayByte, output);
}

void base64_to_string(const base64 &input, std::string &output)
{
    /** Convert a base64 string into usual representation of string.
     * @param   input       Base64 string.
     * @param   output      Usual representation of string.
     */
    
    uint8_t *arrayBytes;
    int lenArrayBytes;
    base64_to_hex_array(input, lenArrayBytes, arrayBytes);
    output.assign(arrayBytes, arrayBytes + lenArrayBytes);
}
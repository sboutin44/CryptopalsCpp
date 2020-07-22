#include "lib.hxx"
#include "c03.hxx"

/* 
    English letters frequency, form : 
    https://www.apprendre-en-ligne.net/crypto/stat/anglais.html 
*/
std::map <char, float> letterFrequency = {
    {'a', 8.08}, {'b', 1.67}, {'c', 3.18}, {'d', 3.99}, {'e', 12.56}, 
    {'f', 2.17}, {'g', 1.80}, {'h', 5.27}, {'i', 7.24}, {'j', 0.14}, {'k', 0.63}, 
    {'l', 4.04}, {'m', 2.60}, {'n', 7.38}, {'o', 7.47}, {'p', 1.91}, {'q', 0.09}, {'r', 6.42}, 
    {'s', 6.59}, {'t', 9.15}, {'u', 2.79}, {'v', 1.00}, {'w', 1.89}, {'x', 0.21}, {'y', 1.65}, {'z', 0.07}
    };

void decode_bytes(const uint8_t* input, const int lenInput, \
        const uint8_t key, int &lenOutput, uint8_t* &output)
{
/** @brief  Decode a bytes array where each byte is xor'd with byte key.
 *  @param  input       Encrypted input array of bytes.
 *  @param  lenInput    Length of input array.
 *  @param  key         Decryption key.
 *  @param  lenOutput   Length of output array.
 *  @param  output      Decrypted array of bytes.
 */

    lenOutput = lenInput;
    output = new uint8_t[lenOutput];

    for (int i = 0; i < lenOutput; i++)
        output[i] = input[i] ^ key;
}

bool isPrintable(std::string inputStr)
{
/** @brief  Check if a string is printable.
 *  @param  inputStr    String that we want to know if it is printable.
 */

    bool printable = true;

    for (unsigned int i = 0; (i < inputStr.length()) && printable; i++)
    {
        printable = isprint(inputStr[i]);
    }
    return printable;    
}

void compute_string_score(const std::string input, float& score)
{
/** @brief  Compute the score of input string, using norm L1 between letter in string and english letter frequency 
 *  @param  input       String that we want to compute score.
 *  @param  score       Score attribued to input string.
 */

    int lenInput = input.size();
    std::map <char, int> frequency;
    score = 0.0;

    /* Get occurence of each character in the input string */
    for (int i = 0; i < lenInput; i++)
    {
        ++frequency[tolower(input[i])];
    }

    /* Compute score using norme L1 */
    for (auto const &it : frequency)
    {
        score += std::abs((it.second/(float)lenInput) - letterFrequency[it.first]);
    }
            
}

void single_byte_xor_cipher(const std::string inputStr, uint8_t &key, std::string &outputStr)
{
/** @brief  Take a hex encoded string which is xor'd encrypted with an unknow key and return a decryption of input and de encryption key. 
 *  @param  inputStr    Encrypted hex encoded string with an unknow key.
 *  @param  key         Key which encrypt input and that we looking for.
 *  @param  outputStr   Decryption of input key.
 */

    uint8_t* inputArray;
    int lenInputArray;

    /* Convert string to array of bytes */
    hex_string_to_hex_array(inputStr, lenInputArray, inputArray);

    float bestScore = -1;
    /* Find key in range [0..255] since text is encrypted by a byte */
    for (uint8_t tmpKey = 0; tmpKey < 255; tmpKey++)
    {
        uint8_t* decodedArray;
        int lenDecodedArray;

        decode_bytes(inputArray, lenInputArray, tmpKey, lenDecodedArray, decodedArray);

        /* Firt filter : check if the string is printable */
        std::string decodedString;
        bytes_to_string(decodedArray, lenDecodedArray, decodedString);

        if (!isPrintable(decodedString))
            continue;

        /* Second filter : compute the score of the best text */
        float score;
        compute_string_score(decodedString, score);

        if (bestScore < score)
        {
            bestScore = score;
            outputStr = decodedString;
            key = tmpKey;

        }                
    }    
}
#include "lib.hxx"
#include "c01.hxx"
#include "test_c01.hxx"

/* reference : https://en.wikipedia.org/wiki/Base64 */

void test_encode_to_base64()
{
    std::vector<std::string> input;
    input.push_back("any carnal pleasure.");
    input.push_back("any carnal pleasure");
    input.push_back("any carnal pleasur");
    input.push_back("any carnal pleasu");
    input.push_back("any carnal pleas");
    input.push_back("pleasure.");
    input.push_back("leasure.");
    input.push_back("easure.");
    input.push_back("asure.");
    input.push_back("sure.");

    std::vector<std::string> expectedOutput;
    expectedOutput.push_back("YW55IGNhcm5hbCBwbGVhc3VyZS4=");
    expectedOutput.push_back("YW55IGNhcm5hbCBwbGVhc3VyZQ==");
    expectedOutput.push_back("YW55IGNhcm5hbCBwbGVhc3Vy");
    expectedOutput.push_back("YW55IGNhcm5hbCBwbGVhc3U=");
    expectedOutput.push_back("YW55IGNhcm5hbCBwbGVhcw==");
    expectedOutput.push_back("cGxlYXN1cmUu");
    expectedOutput.push_back("bGVhc3VyZS4=");
    expectedOutput.push_back("ZWFzdXJlLg==");
    expectedOutput.push_back("YXN1cmUu");
    expectedOutput.push_back("c3VyZS4=");

    bool isTestPassed = true;
    for (unsigned int i = 0; i < input.size(); i++)
    {
        base64 output;
        string_to_base64(input[i], output);
        isTestPassed = isTestPassed && (output == expectedOutput[i]);
    }
    
    printf("-----------------------------------------------------\n");
    printf("Test base64 encoding.\n");
    printf("Test result is: %s.\n", (isTestPassed ? "OK" : "KO"));
    printf("-----------------------------------------------------\n\n");

    /*challeng commes from : https://cryptopals.com/sets/1/challenges/1 */
    if (isTestPassed)
    {

        std::string challenge = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
        base64 outputChallenge;
        uint8_t* tempOutput;
        int lenTempOutput;

        hex_string_to_hex_array(challenge, lenTempOutput, tempOutput);
        hex_array_to_base64(tempOutput, lenTempOutput, outputChallenge);
        
        printf("Challenges / Set 1 / Challenge 1 :\n");
        std::cout << "Input: " << challenge << std::endl;
        std::cout << "Output: " << outputChallenge << std::endl;
    } 
    printf("-----------------------------------------------------\n");   
}

void test_decode_from_base64()
{
    std::vector<std::string> input;
    input.push_back("YW55IGNhcm5hbCBwbGVhc3VyZS4=");
    input.push_back("YW55IGNhcm5hbCBwbGVhc3VyZQ==");
    input.push_back("YW55IGNhcm5hbCBwbGVhc3Vy");
    input.push_back("YW55IGNhcm5hbCBwbGVhc3U=");
    input.push_back("YW55IGNhcm5hbCBwbGVhcw==");
    input.push_back("cGxlYXN1cmUu");
    input.push_back("bGVhc3VyZS4=");
    input.push_back("ZWFzdXJlLg==");
    input.push_back("YXN1cmUu");
    input.push_back("c3VyZS4=");
    
    std::vector<std::string> expectedOutput;
    expectedOutput.push_back("any carnal pleasure.");
    expectedOutput.push_back("any carnal pleasure");
    expectedOutput.push_back("any carnal pleasur");
    expectedOutput.push_back("any carnal pleasu");
    expectedOutput.push_back("any carnal pleas");
    expectedOutput.push_back("pleasure.");
    expectedOutput.push_back("leasure.");
    expectedOutput.push_back("easure.");
    expectedOutput.push_back("asure.");
    expectedOutput.push_back("sure.");

    bool isTestPassed = true;
    for (unsigned int i = 0; i < input.size(); i++)
    {
        std::string output;
        base64_to_string(input[i], output);
        isTestPassed = isTestPassed && (output == expectedOutput[i]);
    }
    
    printf("-----------------------------------------------------\n");
    printf("Test base64 decoding.\n");
    printf("Test result is: %s.\n", (isTestPassed ? "OK" : "KO"));
    printf("-----------------------------------------------------\n\n");
    
    if (isTestPassed)
    {
        base64 challenge = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
        std::string outputChallenge;
        uint8_t* tempOutput;
        int lenTempOutput;

        base64_to_hex_array(challenge, lenTempOutput, tempOutput);
        hex_array_to_hex_string(tempOutput, lenTempOutput, outputChallenge);
        
        printf("Challenges / Set 1 / Challenge 1 :\n");
        std::cout << "Input: " << challenge << std::endl;
        std::cout << "Output: " << outputChallenge << std::endl;
    } 
    printf("-----------------------------------------------------\n");   
}

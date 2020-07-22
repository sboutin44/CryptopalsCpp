#include <iostream>
#include "lib.hxx"
#include "c01.hxx"
#include "c02.hxx"
#include "c03.hxx"

using namespace std;

/* Number of Challenge to compilate */
#define TEST 03


int main()
{

   #if TEST == 01

      test_encode_to_base64();
      test_decode_from_base64();

   #elif TEST == 02
      bool isTestSuccess = test_fixed_xor();
      printf("-----------------------------------------------------\n");
      printf("Test Fixed XOR\n");
      printf("Test result is: %s.\n", (isTestSuccess ? "OK" : "KO"));
      printf("-----------------------------------------------------\n\n");

      std::string challengeInput0 = "1c0111001f010100061a024b53535009181c";
      std::string challengeInput1 = "686974207468652062756c6c277320657965";
      std::string challengeOutput;

      fixed_xor(challengeInput0, challengeInput1, challengeOutput);

      printf("Challenges / Set 1 / Challenge 2 :\n");
      std::cout << "Input 1: \t" << challengeInput0 << std::endl;
      std::cout << "Input 2: \t" << challengeInput1 << std::endl;
      std::cout << "Output: \t" << challengeOutput << std::endl;
      printf("-----------------------------------------------------\n\n");

   #elif TEST == 03

      bool isTestSuccess = test_single_byte_xor_cipher();

      printf("-----------------------------------------------------\n");
      printf("Test Single Byte XOR Cipher\n");
      printf("Test result is: %s.\n", (isTestSuccess ? "OK" : "KO"));
      printf("-----------------------------------------------------\n\n");

      std::string challengeInput = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
      std::string challengeOutput;
      uint8_t decryptionKey;

      single_byte_xor_cipher(challengeInput, decryptionKey, challengeOutput);

      printf("Challenges / Set 1 / Challenge 3 :\n");
      std::cout << "Input:  \t" << challengeInput << std::endl;
      std::cout << "Output: \t" << challengeOutput << std::endl;
      std::cout << "Decryption key:\t" << (int)decryptionKey << std::endl;
      printf("-----------------------------------------------------\n\n");

   #endif
}

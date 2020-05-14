#include "aes.h"
#include "lib.h"
using namespace std;

void AES128_ECB_decrypt(byte* ciphertext, byte* key, int len, byte* plaintext) {
  /** Decrypt an AES encrypted bytes string with ECB mode. */

  int block_size = 16;

  for (int i = 0; i < len; i += block_size) {
    invAES128(&ciphertext[i], key, &plaintext[i]);
  }
}

void AES128_ECB_encrypt(byte* plaintext, byte* key, int plain_len,
                        byte* ciphertext) {
  /** Decrypt an AES encrypted bytes string with ECB mode. */

  int block_size = 16;

  for (int i = 0; i < plain_len; i += block_size) {
    AES128(&plaintext[i], key, &ciphertext[i]);
  }
}

void challenge_7() {
  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 1" << endl;
  cout << "7. AES in ECB mode" << endl;
  cout << "------------------------------------\n" << endl;

  int len = 0;
  byte* ciphertext = read_base64_file("resources/7.txt", &len);
  byte* plaintext = new byte[len];
  const char* key = "YELLOW SUBMARINE";

  AES128_ECB_decrypt(ciphertext, (byte*)key, len, plaintext);
  for (int j = 0; j < len; j++) printf("%c", plaintext[j]);

  delete[] plaintext;
  delete[] ciphertext;
}

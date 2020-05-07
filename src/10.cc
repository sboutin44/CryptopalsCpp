#include "aes.h"
#include "lib.h"

using namespace std;

void AES128_CBC_encrypt(byte* plaintext, byte* key, byte* ciphertext, int len) {
  int blocksize = 16;
  byte* buffer = new byte[len];

  const byte IV[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  // First block
  for (int j = 0; j < blocksize; j++) buffer[j] = IV[j] ^ plaintext[j];
  // for (int j = 0; j < len; j++) printf("%c ", buffer[j]);
  AES128(buffer, key, ciphertext);
  printf("\n ");
  // for (int j = 0; j < len; j++) printf("%02x ", ciphertext[j]);

  for (int i = blocksize; i < len; i += blocksize) {
    // XOR with previous block
    for (int j = 0; j < blocksize; j++)
      buffer[i + j] = ciphertext[i - blocksize + j] ^ plaintext[i + j];

    AES128(&buffer[i], key, &ciphertext[i]);
  }
  delete[] buffer;
}

void AES128_CBC_decrypt(byte* ciphertext, byte* key, byte* plaintext, int len) {
  int blocksize = 16;
  byte* buffer = new byte[len];

  const byte IV[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  for (int i = len - blocksize; i >= blocksize; i -= blocksize) {
    invAES128(&ciphertext[i], key, &buffer[i]);

    // XOR with previous block
    for (int j = 0; j < blocksize; j++)
      plaintext[i + j] = ciphertext[i - blocksize + j] ^ buffer[i + j];
  }

  invAES128(ciphertext, key, buffer);

  // First block
  for (int j = 0; j < blocksize; j++) plaintext[j] = IV[j] ^ buffer[j];

  delete[] buffer;
}

void challenge_10() {
  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 2" << endl;
  cout << "10. Implement CBC mode" << endl;
  cout << "------------------------------------\n" << endl;

  // Allocate a buffer with the padded plaintext
  const char* key = "YELLOW SUBMARINE";
  const char* plaintext = "Text clair pour voir si ça marche";
  int blocksize = 16;
  int len = strlen(plaintext);
  int pad_len = blocksize - len % blocksize;
  int len_out = len + pad_len;  // Multiple of the AES block size.
  byte* my_plaintext = new byte[len_out];
  byte* buffer = new byte[len_out];
  byte* ciphertext_CBC = new byte[len_out];

  PKCS7_padding((byte*)plaintext, len, buffer, blocksize);

  // test if CBC mode works
  printf("\n---------------\n");
  AES128_CBC_encrypt((byte*)buffer, (byte*)key, ciphertext_CBC, len_out);

  AES128_CBC_decrypt((byte*)ciphertext_CBC, (byte*)key, my_plaintext, len_out);
  for (int j = 0; j < len_out; j++) printf("%c", my_plaintext[j]);
  printf("\n---------------\n");

  // Challenge
  int l = 0;
  byte* ciphertext_10 = read_base64_file("resources/10.txt", &l);
  byte* plaintext_10 = new byte[l];
  AES128_CBC_decrypt((byte*)ciphertext_10, (byte*)key, plaintext_10, l);
  for (int j = 0; j < l; j++) printf("%c", plaintext_10[j]);
  printf("\n ");
}

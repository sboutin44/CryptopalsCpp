#include "aes.h"
#include "lib.h"
using namespace std;

void challenge_8() {
  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 1" << endl;
  cout << "8. Detect AES in ECB mode" << endl;
  cout << "------------------------------------\n" << endl;

  int len = 0;
  const char* hex_ciphertext = read_text_file("resources/8.txt", &len);
  byte* ciphertext = new byte[len / 2];
  hexDecode(hex_ciphertext, ciphertext);

  // for (int )

  delete[] ciphertext;
}

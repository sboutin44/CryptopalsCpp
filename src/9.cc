#include "aes.h"
#include "lib.h"

using namespace std;

int PKCS7_padding(byte* in, int lenIn, byte* out, int blocksize) {
  /** Add padding to a pre-allocated array. */

  int pad_len = blocksize - lenIn % blocksize;
  byte pad_byte = pad_len;

  memcpy(out, in, lenIn);
  for (int i = 0; i < pad_len; i++) out[lenIn + i] = pad_byte;
}

void challenge_9() {
  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 2" << endl;
  cout << "9. Implement PKCS#7 padding" << endl;
  cout << "------------------------------------\n" << endl;

  int blocksize = 20;
  const char* str = "YELLOW SUBMARINE";
  int len = strlen(str);
  int pad_len = blocksize - len % blocksize;
  byte* padded_str = new byte[len + pad_len];

  PKCS7_padding((byte*)str, len, padded_str, blocksize);

  cout << "Length string:   \t" << len << endl;
  cout << "Length padding:  \t" << pad_len << endl;
  cout << "Length padded string: \t" << len + pad_len << endl;
  cout << "Result: \t" << endl;

  for (int j = 0; j < len + pad_len; j++) printf("%02x ", padded_str[j]);
}

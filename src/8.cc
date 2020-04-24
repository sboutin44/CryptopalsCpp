#include <inttypes.h>

#include "aes.h"
#include "lib.h"
using namespace std;

void challenge_8() {
  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 1" << endl;
  cout << "8. Detect AES in ECB mode" << endl;
  cout << "------------------------------------\n" << endl;

  const char* filename = "resources/8.txt";
  map<uint64_t, string> m;  // Map a hamming distance to a cipher.
  int block_size = 16;
  int len = 0;
  int nb_ciphertexts = countLines(filename);  // 1 line = 1 ciphertext
  byte** ciphers = new byte*[nb_ciphertexts];

  cout << "nb_ciphertexts: " << nb_ciphertexts << endl;

  // Read all ciphertexts 1 by 1.
  ifstream file;

  uint64_t* hamming_distances = new uint64_t[nb_ciphertexts];
  for (int j = 0; j < nb_ciphertexts; j++) hamming_distances[j] = 0;

  file.open(filename);

  // file.open(filename);
  int i = 0;
  int len_ciphertext;

  for (std::string line; std::getline(file, line);) {
    assert(i < nb_ciphertexts);

    // A 2-chars string "AB" will tranlate to a single byte 0xAB with hexDecode.
    len_ciphertext = line.length() / 2;
    ciphers[i] = new byte[len_ciphertext];
    memset(ciphers[i], 0, len_ciphertext);
    hexDecode(line.c_str(), ciphers[i]);

    // Compute hamming distances between all blocks
    for (int j = 0; j < len_ciphertext; j += block_size) {
      for (int k = j + block_size; k < len_ciphertext; k += block_size) {
        hamming_distances[i] +=
            hammingDistance(&ciphers[i][j], &ciphers[i][k], block_size);
      }
    }

    m[hamming_distances[i]] = line;
    if (hamming_distances[i] == 2398)
      cout << "Line in the file: " << i + 1
           << endl;  // Lines start a 1 in my editor

    i++;
  }

  file.close();

  // line 132:
  // const char* c_hex =
  // "5c4ca78f8de3527788e7d1efcd6aad0adc3878ea70993ae20937ef0a601730494946f078de2099c62de9af1c47ee4f18216ed5a7268464f210374dbf421d55449c8f399d8824c5a0ff8526a940223ee999a6f945f0ba3eaa672c434ad867ac7adaa46bd3289729c6c7d920dd0d8237bf678d88bde91e0683e72e88fef50bdb23cceb6270acba5aeebd0a834ccf99cd3e6bad8c158f5819f1f1c785fdaa3df505";
  // line 133:
  // const char* c_hex =
  // "d880619740a8a19b7840a8a31c810a3d08649af70dc06f4fd5d2d69c744cd283e2dd052f6b641dbf9d11b0348542bb5708649af70dc06f4fd5d2d69c744cd2839475c9dfdbc1d46597949d9c7e82bf5a08649af70dc06f4fd5d2d69c744cd28397a93eab8d6aecd566489154789a6b0308649af70dc06f4fd5d2d69c744cd283d403180c98c8f6db1f2a3f9c4040deb0ab51b29933f2c123c58386b06fba186a";
  // line 134:
  // const char* c_hex =
  // "b563aac8275730bd4cf89ab32bb4b152be8fae16afab58ab3ea0e825c8ce28ddbe26c8cafef763f1d9c3f30d60335cd0b765b98a11d5cfbe7a2d75e8f8a5e851ee6a17de174d8bea5c1e089beffc99709d6dcc03e578220eccdfa99d3fa0a3d2f6736de041cd783ad7f866df5dcd2a752cfbfc380cf84da5c5dd3fc486cf1adc14d29d9e91737514e8c67d5c5aece4a19216e2b069f53b8ab4acaef17f815004";

  uint64_t a_min = min(hamming_distances, nb_ciphertexts);
  string ciphertext_s = m[a_min];
  len = ciphertext_s.length() / 2;
  // const char* key    = "YELLOW SUBMARINE";
  // byte* plaintext = new byte[len];
  byte* c = new byte[len];
  hexDecode(ciphertext_s.c_str(), c);

  cout << "\nDisplay 16-bytes blocks, one per line, to see the similarities:"
       << endl;
  for (int j = 0; j < len; j++) {
    if (j % 16 == 0) printf("\n");
    printf("%02x", c[j]);
  }
  printf("\n");

  // I don't know the key... YELLOW SUBMARINE doesn't work.
  // AES128_ECB_decrypt(c, (byte*)key, len, plaintext);
  // for (int j = 0; j < len; j++) printf("%c", plaintext[j]);

  delete[] hamming_distances;
}

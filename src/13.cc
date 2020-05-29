// Copyright © 2020 Sebastien BOUTIN
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
// Except as contained in this notice, the name(s) of the above copyright
// holders shall not be used in advertising or otherwise to promote the sale,
// use or other dealings in this Software without prior written authorization.

#include "lib.h"

using namespace std;
// byte* key = new byte[AES128_BLOCKSIZE];
byte key[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d,
                0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
byte to_inject[] = {0x2b, 0xc4, 0xb6, 0x77, 0x0f, 0x35, 0x2f, 0x42,
                    0xc6, 0x3f, 0x59, 0x28, 0xec, 0x83, 0x21, 0x1f};

int len_ciphertext_ECB;
byte* ciphertext_ECB;

void printProfile(Profile m) {
  cout << "{\n  "
       << "email: '" << m.email << "',\n";
  cout << "  uid:'" << m.uid << "',\n";
  cout << "  role: '" << m.role << "'\n}\n";
}

void printJsonStyle(map<string, string> m) {
  cout << "{" << endl;
  for (auto it = m.begin(); it != m.end(); it++) {
    cout << "  " << it->first << ": "
         << "'" << it->second << "'"
         << "," << endl;
  }
  cout << "}" << endl;
  cout << endl;
}

Profile parse(string s) {
  Profile profile;
  int pos0 = 0;
  int pos1 = 0;
  int pos2 = 0;
  int nb_args = 0;

  while (pos2 != -1) {
    // Find the first '='
    pos0 = 0;
    pos1 = s.find('=');
    pos2 = s.find('&');
    string key = s.substr(pos0, pos1 - pos0);
    string val = s.substr(pos1 + 1, pos2 - (pos1 + 1));

    if (key == "email") profile.email = val;

    if (key == "uid") profile.uid = stoi(val);

    if (key == "role") profile.role = val;

    // Set next position and redefine the substring we work on.
    pos0 = pos2 + 1;
    s = s.substr(pos0, s.length());

    nb_args++;
  }

  assert(nb_args == 3);  // Check we have only email, uid and role.

  return profile;
}

string profile_for(string email) {
  /* Returns an empty string if a character not allowed is detected. */

  if (email.find_first_of("&=") == string::npos) {
    string role = "user";
    int uid = rand() % 100;
    //	Profile profile = { .email = email , .uid = uid , .role = role};
    string encoded_profile =
        "email=" + email + "&uid=" + to_string(uid) + "&role=" + role;
    return encoded_profile;
  } else {
    //		cerr << "Characters not allowed : & or =" << endl;
    string empty = "";
    return empty;
  }
}

void functionA(string in) {
  string my_profile_encoded = profile_for(in);

  // Function A: Encrypt the encoded user profile
  len_ciphertext_ECB = PKCS7_getSize((byte*)my_profile_encoded.c_str(),
                                     my_profile_encoded.length());
  ciphertext_ECB = new byte[len_ciphertext_ECB];
  byte* buffer = new byte[len_ciphertext_ECB];
  PKCS7_padding((byte*)my_profile_encoded.c_str(), my_profile_encoded.length(),
                buffer, AES128_BLOCKSIZE);

  cout << "Padded input" << endl;
  printByteArray(buffer, len_ciphertext_ECB);

  AES128_ECB_encrypt((byte*)buffer, (byte*)key, len_ciphertext_ECB,
                     ciphertext_ECB);

  cout << "Ciphertext:" << endl;
  printByteArray(ciphertext_ECB, len_ciphertext_ECB);
}

void functionB() {
  /* Decrypt a profile after replacing the last encrypted block by a custom
   * encrypted block. */

  // ------------------------------------------------------------------
  // attack: insert the encrypted text with admin role:
  for (int i = 0; i < 16; i++) ciphertext_ECB[2 * 16 + i] = to_inject[i];
  // ------------------------------------------------------------------

  byte* padded_plaintext = new byte[len_ciphertext_ECB];
  AES128_ECB_decrypt(ciphertext_ECB, key, len_ciphertext_ECB, padded_plaintext);
  int len_plaintext =
      len_ciphertext_ECB -
      PKCS7_getPaddingSize(padded_plaintext, len_ciphertext_ECB);

  byte* plaintext = new byte[len_plaintext];
  memcpy(plaintext, padded_plaintext, len_plaintext);

  // Convert to a C++ string
  string encoded_admin_profile = "";
  for (int i = 0; i < len_plaintext; i++) {
    string c(1, plaintext[i]);
    encoded_admin_profile += c;
  }

  Profile admin_profile = parse(encoded_admin_profile);
  printProfile(admin_profile);
}

void challenge_13() {
  /** The goal here is to create an admin profile by modifying the last
   * encrypted block with a custom block containing "admin" and the padding.
   */

  cout << "\n------------------------------------" << endl;
  cout << "Challenges Set 2" << endl;
  cout << "13. ECB cut-and-paste" << endl;
  cout << "------------------------------------\n" << endl;

  srand(time(NULL));

  // Uncomment to create the last encrypted block
  //  string block0 =
  //      "aaaaaaaaaa";  // expanded to the 16-bytes string 'email=aaaaaaaaaa'
  //  string block1 = "admin";  // designed to be 'admin\0xb\0xb...\xb'
  //  int pad_value = 16 - block1.length();
  //  for (int i = 0; i < pad_value; i++) {
  //    block1 += (byte)pad_value;
  //  }
  //  functionA(block0+block1);

  // After the creation of the 'admin' encrypted block (filled with padding):
  //'admin\0xb\0xb...\xb' encrypted:  {0x2b,0xc4 ,0xb6 ,0x77 ,0x0f ,0x35 ,0x2f
  //,0x42 ,0xc6 ,0x3f ,0x59 ,0x28 ,0xec ,0x83 ,0x21 ,0x1f};

  // We can then give profile_for() an email long enough to fill 2 blocks of
  // AES128, so that when we intercept the encrypted profile we'll just have to
  // replace the end by our previous finding:
  //  aaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaa aaaaaaaaaaaaaaaa
  //  email=foooo@bar. com&uid=10&role= ______to_replace

  // Here is the email long enough, the issue lies when the uid length varies.
  string email = "foooo@bar.com";
  cout << "foooo@bar.com" << endl;

  functionA(email);
  functionB();
}

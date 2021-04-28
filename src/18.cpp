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

bytearray_t* AES_128_CTR_enc();
bytearray_t* AES_128_CTR_dec();

bytearray_t* AES_CTR_enc(bytearray_t* plain, byte* key) {
	bytearray_t* ciphertext;
	//ciphertext->data_ptr = new byte[plain->l];
	
	// Padding
	ciphertext->data_ptr = PKCS7_padding2(plain->data_ptr,plain->l, AES_128_BLOCKSIZE);

	byte* nounce = new byte[8];
	// In our case the nounce will just be 0.
	memset(nounce,0,8);
	byte* counter = new byte[8];
	memset(counter, 0, 8);
	//byte* keystream = 

	// TODO: remove when the function is done
	bytearray_t* a;
	return a;
}

bytearray_t* AES_CTR_dec() {
	bytearray_t* a;
	return a;
}


void challenge_18() {
	// Implement AES CTR mode.

	string plainBased64Encoded = "L77na/nrFsKvynd6HzOoG7GHTLXsTVu9qvY/2syLXzhPweyyMTJULu/6/kXX0KSvoOLSFQ==";


}
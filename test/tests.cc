#include "lib.h"
using namespace std;

void testHammingDistance() {
  const char* a = "this is a test";
  const char* b = "wokka wokka!!!";

  const char* c = "this is a testwokka wokka!!!";

  int len_a = strlen(a);

  // Basic test
  int d1 = hammingDistance((uint8_t*)a, (uint8_t*)b, len_a);

  // Checks that is works within the same byte string.
  int d2 = hammingDistance((uint8_t*)c, (uint8_t*)&c[len_a], len_a);
  int d3 = hammingDistance((uint8_t*)c, (uint8_t*)c + len_a, len_a);

  assert(d1 == 37);
  assert(d2 == 37);
  assert(d3 == 37);

  cout << "testHammingDistance passed" << endl;
}

void testInsertionSort() {
  float a[] = {9.3, 0.1, 0.0003, 99.001, 3};
  float a_sorted[] = {0.0003, 0.1, 3, 9.3, 99.001};

  int len = sizeof(a) / sizeof(float);
  insertionSort(a, len);

  assert(memcmp((float*)a, (float*)a_sorted, len) == 0);
  cout << "testInsertionSort passed" << endl;
}

void testIndexOfCoincidence() {
  // Load an english text.
  int N1, N2, N3, N4, N5, N6, N7;
  const char* filename1 = "resources/aliceadventures.txt";
  const char* filename2 = "resources/dummy_text.txt";
  const char* filename3 = "resources/gpl-3.0.txt";
  const char* filename4 = "resources/earth.txt";
  const char* filename5 = "resources/history.txt";
  const char* filename6 = "resources/michael.txt";
  const char* filename7 = "resources/united_states.txt";

  // float I1 = indexOfCoincidence(text1, N);
  // float I2 = indexOfCoincidence(text2, N);

  // cout << indexOfCoincidence_(text1, N1) << endl;
  // cout << indexOfCoincidence_(text2, N2) << endl;
  // cout << indexOfCoincidence_(text3, N3) << endl;
  printf("%f\n",
         indexOfCoincidence_((uint8_t*)read_text_file(filename1, &N1), N1));
  printf("%f\n",
         indexOfCoincidence_((uint8_t*)read_text_file(filename2, &N2), N2));
  printf("%f\n",
         indexOfCoincidence_((uint8_t*)read_text_file(filename3, &N3), N3));
  printf("%f\n",
         indexOfCoincidence_((uint8_t*)read_text_file(filename4, &N4), N4));
  printf("%f\n",
         indexOfCoincidence_((uint8_t*)read_text_file(filename5, &N5), N5));
  printf("%f\n",
         indexOfCoincidence_((uint8_t*)read_text_file(filename6, &N6), N6));
  printf("%f\n",
         indexOfCoincidence_((uint8_t*)read_text_file(filename7, &N7), N7));
}

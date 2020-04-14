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

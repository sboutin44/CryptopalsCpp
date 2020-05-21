#include "Vector.h"

Vector::Vector() {}

void Vector::push_back(bytearray_t arr) {
  // Hard copy of an array in the private vector of the class.

  bytearray_t heap_cpy;
  heap_cpy.l = arr.l;
  memcpy(heap_cpy.data_ptr, arr.data_ptr, arr.l);
  entries.push_back(heap_cpy);
}

void Vector::push_back(const byte* arr, int l) {
  // Hard copy of an array in the private vector of the class.

  bytearray_t heap_cpy;
  heap_cpy.l = l;
  heap_cpy.data_ptr = new byte[l];
  memcpy(heap_cpy.data_ptr, arr, l);
}

void Vector::printEntries() {
  for (auto it = entries.begin(); it != entries.end(); it++) {
    bytearray_t entry = *it;
    std::cout << "c1: ";
    printByteArray(entry.data_ptr, entry.l);
  }
}

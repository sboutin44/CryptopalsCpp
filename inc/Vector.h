#ifndef CRYPTOPALS_INC_VECTOR_H_
#define CRYPTOPALS_INC_VECTOR_H_

#include "lib.h"

class Vector {
  /* Wrapper for std::vector to easily work with vectors of arrays. */

 private:
  std::vector<bytearray_t> entries;

 public:
  Vector();
  void push_back(bytearray_t arr);
  void push_back(const byte* arr, int l);
  void printEntries();
};

#endif  // CRYPTOPALS_INC_VECTOR_H_

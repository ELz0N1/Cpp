#ifndef READER_HEADER
#define READER_HEADER
#include <string>

#include "io.hpp"

class Reader : virtual public IO {
 public:
  virtual Reader& operator>>(std::string& str) = 0;
  virtual Reader& operator>>(int& i) = 0;
  virtual Reader& operator>>(char& ch) = 0;
};

#endif
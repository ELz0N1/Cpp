#ifndef WRITER_HEADER
#define WRITER_HEADER
#include <string>

#include "io.hpp"

class Writer : virtual public IO {
 public:
  virtual Writer& operator<<(std::string& str) = 0;
  virtual Writer& operator<<(int& i) = 0;
  virtual Writer& operator<<(char& ch) = 0;
};

#endif
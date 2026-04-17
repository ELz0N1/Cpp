#ifndef STRING_HEADER
#define STRING_HEADER

#include <string>

#include "io.hpp"
#include "reader.hpp"
#include "readerwriter.hpp"
#include "writer.hpp"

class StringIO : virtual public IO {
 protected:
  std::string string_;
  size_t idx = 0;

 public:
  StringIO(std::string input) : string_(input) { open_ = true; }
  void close() override { open_ = false; }
  bool eof() const override { return idx >= string_.size(); }
};

class StringReader : virtual public StringIO, virtual public Reader {
 public:
  StringReader(std::string input) : StringIO(input) {}

  StringReader& operator>>(std::string& str) override;
  StringReader& operator>>(char& ch) override;
  StringReader& operator>>(int& i) override;
};

class StringWriter : virtual public StringIO, virtual public Writer {
 public:
  StringWriter(std::string input) : StringIO(input) {}

  StringWriter& operator<<(std::string& str) override;
  StringWriter& operator<<(char& ch) override;
  StringWriter& operator<<(int& i) override;
};

class StringReaderWriter : virtual public StringReader,
                           virtual public StringWriter,
                           virtual public ReaderWriter {
 public:
  StringReaderWriter(std::string input)
      : StringIO(input), StringReader(input), StringWriter(input) {}
};

#endif
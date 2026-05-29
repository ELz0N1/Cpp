#ifndef BUFFERED_STRING_HEADER
#define BUFFERED_STRING_HEADER

#include <string>

#include "buffered_io.hpp"
#include "readerwriter.hpp"
#include "string.hpp"

class BufferedStringIO : virtual public StringIO, virtual public BufferedIO {
 protected:
  bool refillReadBuffer() override;
  void flushWriteBuffer() override;

 public:
   BufferedStringIO(std::string input) : StringIO(input) {}

  void close() override;
  ~BufferedStringIO() override { flushWriteBuffer(); }
};

class BufferedStringReader : virtual public BufferedStringIO,
                             virtual public StringReader {
 public:
   BufferedStringReader(std::string input)
      : StringIO(input), BufferedStringIO(input), StringReader(input) {}

  BufferedStringReader& operator>>(std::string& str) override;
  BufferedStringReader& operator>>(char& ch) override;
  BufferedStringReader& operator>>(int& i) override;
};

class BufferedStringWriter : virtual public BufferedStringIO,
                             virtual public StringWriter {
 public:
   BufferedStringWriter(std::string input)
      : StringIO(input), BufferedStringIO(input), StringWriter(input) {}

  BufferedStringWriter& operator<<(std::string& str) override;
  BufferedStringWriter& operator<<(char& ch) override;
  BufferedStringWriter& operator<<(int& i) override;
};

class BufferedStringReaderWriter : virtual public BufferedStringReader,
                                   virtual public BufferedStringWriter,
                                   virtual public ReaderWriter {
 public:
  BufferedStringReaderWriter(std::string input)
      : StringIO(input),
        BufferedStringIO(input),
        StringReader(input),
        StringWriter(input),
        BufferedStringReader(input),
        BufferedStringWriter(input) {}
};

#endif

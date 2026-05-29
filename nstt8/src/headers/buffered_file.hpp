#ifndef BUFFERED_FILE_HEADER
#define BUFFERED_FILE_HEADER

#include <string>

#include "buffered_io.hpp"
#include "file.hpp"
#include "readerwriter.hpp"

class BufferedFileIO : virtual public FileIO, virtual public BufferedIO {
 protected:
  bool refillReadBuffer() override;
  void flushWriteBuffer() override;

 public:
  BufferedFileIO(std::string path, const char* mode) : FileIO(path, mode) {}

  void close() override;
  ~BufferedFileIO() override { flushWriteBuffer(); }
};

class BufferedFileReader : virtual public BufferedFileIO, virtual public FileReader {
 public:
   BufferedFileReader(std::string path)
      : FileIO(path, "r"), BufferedFileIO(path, "r"), FileReader(path) {}

  BufferedFileReader& operator>>(std::string& str) override;
  BufferedFileReader& operator>>(char& ch) override;
  BufferedFileReader& operator>>(int& i) override;
};

class BufferedFileWriter : virtual public BufferedFileIO, virtual public FileWriter {
 public:
   BufferedFileWriter(std::string path)
      : FileIO(path, "w"), BufferedFileIO(path, "w"), FileWriter(path) {}

  BufferedFileWriter& operator<<(std::string& str) override;
  BufferedFileWriter& operator<<(char& ch) override;
  BufferedFileWriter& operator<<(int& i) override;
};

class BufferedFileReaderWriter : virtual public BufferedFileReader,
                                 virtual public BufferedFileWriter,
                                 virtual public ReaderWriter {
 public:
  BufferedFileReaderWriter(std::string path)
      : FileIO(path, "r+"),
        BufferedFileIO(path, "r+"),
        FileReader(path),
        FileWriter(path),
        BufferedFileReader(path),
        BufferedFileWriter(path) {}

  void rewind() {
    flushWriteBuffer();
    resetReadBuffer();
    resetWriteBuffer();
    if (file_) {
      clearerr(file_);
      ::fseek(file_, 0, SEEK_SET);
    }
  }
};

#endif

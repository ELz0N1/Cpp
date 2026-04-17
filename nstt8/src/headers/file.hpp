#ifndef FILE_HEADER
#define FILE_HEADER

#include <cstdio>
#include <string>

#include "io.hpp"
#include "reader.hpp"
#include "readerwriter.hpp"
#include "writer.hpp"

class FileNotFoundException : public std::runtime_error {
 public:
  FileNotFoundException(const std::string& filename)
      : std::runtime_error("File not found: " + filename) {}
};

class FileIO : virtual public IO {
 protected:
  FILE* file_;

 public:
  FileIO(std::string path, const char* mode) {
    FILE* file = fopen(path.c_str(), mode);
    if (file != nullptr) {
      file_ = file;
      open_ = true;
    } else {
      throw FileNotFoundException(path);
    }
  }

  void close() override { open_ = false; }
  bool eof() const override { return feof(file_); }

  virtual ~FileIO() {
    if (file_) fclose(file_);
  }
};

class FileReader : virtual public FileIO, virtual public Reader {
 public:
  FileReader(std::string path) : FileIO(path, "r") {}

  FileReader& operator>>(std::string& str) override;
  FileReader& operator>>(char& ch) override;
  FileReader& operator>>(int& i) override;
};

class FileWriter : virtual public FileIO, virtual public Writer {
 public:
  FileWriter(std::string path) : FileIO(path, "w") {}

  FileWriter& operator<<(std::string& str) override;
  FileWriter& operator<<(char& ch) override;
  FileWriter& operator<<(int& i) override;
};

class FileReaderWriter : virtual public FileReader,
                         virtual public FileWriter,
                         virtual public ReaderWriter {
 public:
  FileReaderWriter(std::string path)
      : FileIO(path, "r+"), FileReader(path), FileWriter(path) {}

  void rewind() {
    if (file_) {
      clearerr(file_);
      ::fseek(file_, 0, SEEK_SET);
    }
  }
};

#endif
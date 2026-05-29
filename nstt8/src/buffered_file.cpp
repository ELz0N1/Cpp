#include <cctype>

#include "headers/buffered_file.hpp"

bool BufferedFileIO::refillReadBuffer() {
  flushWriteBuffer();

  if (!file_ || feof(file_)) {
    return false;
  }

  fflush(file_);
  clearerr(file_);

  read_pos_ = 0;
  read_len_ = fread(read_buffer_, 1, buffer_size, file_);

  return read_len_ > 0;
}

void BufferedFileIO::flushWriteBuffer() {
  if (!file_ || write_len_ == 0) {
    return;
  }

  fwrite(write_buffer_, 1, write_len_, file_);
  write_len_ = 0;
}

void BufferedFileIO::close() {
  flushWriteBuffer();
  FileIO::close();
}

BufferedFileReader& BufferedFileReader::operator>>(std::string& str) {
  if (!open_) {
    return *this;
  }

  str.clear();
  char ch = '\0';

  while (bufferedGetChar(ch)) {
    if (!std::isspace(static_cast<unsigned char>(ch))) {
      bufferedPutback(ch);
      break;
    }
  }

  while (bufferedGetChar(ch) && !std::isspace(static_cast<unsigned char>(ch))) {
    str.push_back(ch);
  }

  if (std::isspace(static_cast<unsigned char>(ch))) {
    bufferedPutback(ch);
  }

  return *this;
}

BufferedFileReader& BufferedFileReader::operator>>(char& ch) {
  if (!open_) {
    return *this;
  }

  char holder = '\0';
  while (bufferedGetChar(holder) &&
         !std::isalnum(static_cast<unsigned char>(holder))) {
  }

  if (std::isalnum(static_cast<unsigned char>(holder))) {
    ch = holder;
  }

  return *this;
}

BufferedFileReader& BufferedFileReader::operator>>(int& i) {
  if (!open_) {
    return *this;
  }

  std::string holder;
  char ch = '\0';

  while (bufferedGetChar(ch) && !std::isdigit(static_cast<unsigned char>(ch))) {
  }

  if (std::isdigit(static_cast<unsigned char>(ch))) {
    holder += ch;
  }

  while (bufferedGetChar(ch) && std::isdigit(static_cast<unsigned char>(ch))) {
    holder += ch;
  }

  if (!std::isdigit(static_cast<unsigned char>(ch))) {
    bufferedPutback(ch);
  }

  i = holder.empty() ? 0 : std::stoi(holder);

  return *this;
}

BufferedFileWriter& BufferedFileWriter::operator<<(std::string& str) {
  if (!open_) {
    return *this;
  }

  for (char ch : str) {
    bufferedPutChar(ch);
  }

  return *this;
}

BufferedFileWriter& BufferedFileWriter::operator<<(int& i) {
  if (!open_) {
    return *this;
  }

  for (char ch : std::to_string(i)) {
    bufferedPutChar(ch);
  }

  return *this;
}

BufferedFileWriter& BufferedFileWriter::operator<<(char& ch) {
  if (!open_) {
    return *this;
  }

  bufferedPutChar(ch);

  return *this;
}

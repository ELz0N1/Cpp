#include <cctype>

#include "headers/buffered_string.hpp"

bool BufferedStringIO::refillReadBuffer() {
  flushWriteBuffer();

  if (eof()) {
    return false;
  }

  read_pos_ = 0;
  read_len_ = 0;

  while (read_len_ < buffer_size && idx < string_.size()) {
    read_buffer_[read_len_++] = string_[idx++];
  }

  return read_len_ > 0;
}

void BufferedStringIO::flushWriteBuffer() {
  if (write_len_ == 0) {
    return;
  }

  string_.append(write_buffer_, write_len_);
  write_len_ = 0;
}

void BufferedStringIO::close() {
  flushWriteBuffer();
  StringIO::close();
}

BufferedStringReader& BufferedStringReader::operator>>(std::string& str) {
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

BufferedStringReader& BufferedStringReader::operator>>(char& ch) {
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

BufferedStringReader& BufferedStringReader::operator>>(int& i) {
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

  if (!holder.empty()) {
    i = std::stoi(holder);
  } else {
    i = 0;
  }

  return *this;
}

BufferedStringWriter& BufferedStringWriter::operator<<(std::string& str) {
  if (!open_) {
    return *this;
  }

  for (char ch : str) {
    bufferedPutChar(ch);
  }

  return *this;
}

BufferedStringWriter& BufferedStringWriter::operator<<(int& i) {
  if (!open_) {
    return *this;
  }

  for (char ch : std::to_string(i)) {
    bufferedPutChar(ch);
  }

  return *this;
}

BufferedStringWriter& BufferedStringWriter::operator<<(char& ch) {
  if (!open_) {
    return *this;
  }

  bufferedPutChar(ch);

  return *this;
}

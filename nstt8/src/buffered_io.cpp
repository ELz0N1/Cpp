#include "headers/buffered_io.hpp"

bool BufferedIO::bufferedGetChar(char& ch) {
  if (readBufferEmpty() && !refillReadBuffer()) {
    return false;
  }
  ch = read_buffer_[read_pos_++];
  return true;
}

void BufferedIO::bufferedPutChar(char ch) {
  if (writeBufferFull()) {
    flushWriteBuffer();
  }
  write_buffer_[write_len_++] = ch;
}

void BufferedIO::bufferedPutback(char ch) {
  if (read_pos_ > 0) {
    read_buffer_[--read_pos_] = ch;
    return;
  }

  if (read_len_ < buffer_size) {
    for (size_t i = read_len_; i > 0; --i) {
      read_buffer_[i] = read_buffer_[i - 1];
    }
    read_buffer_[0] = ch;
    ++read_len_;
    read_pos_ = 0;
  }
}

void BufferedIO::resetReadBuffer() {
  read_pos_ = 0;
  read_len_ = 0;
}

void BufferedIO::resetWriteBuffer() {
  write_len_ = 0;
}

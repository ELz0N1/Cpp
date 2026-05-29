#ifndef BUFFERED_IO_HEADER
#define BUFFERED_IO_HEADER

#include <cstddef>

class BufferedIO {
 protected:
  static constexpr size_t buffer_size = 4096;

  char read_buffer_[buffer_size]{};
  size_t read_pos_ = 0;
  size_t read_len_ = 0;

  char write_buffer_[buffer_size]{};
  size_t write_len_ = 0;

  bool readBufferEmpty() const { return read_pos_ >= read_len_; }
  bool writeBufferFull() const { return write_len_ >= buffer_size; }

  virtual bool refillReadBuffer() = 0;
  virtual void flushWriteBuffer() = 0;

  bool bufferedGetChar(char& ch);
  void bufferedPutChar(char ch);
  void bufferedPutback(char ch);

  void resetReadBuffer();
  void resetWriteBuffer();
};

#endif

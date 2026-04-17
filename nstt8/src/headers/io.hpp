#ifndef IO_HEADER
#define IO_HEADER

class IO {
 protected:
  bool open_ = false;

 public:
  virtual void close() = 0;
  virtual bool eof() const = 0;
  virtual ~IO() = default;
};

#endif
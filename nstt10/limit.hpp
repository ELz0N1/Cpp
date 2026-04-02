#ifndef LIMIT_H
#define LIMIT_H

#include <cstddef>
#include <stdexcept>

struct InstanceLimitExceededException : public std::logic_error {
  InstanceLimitExceededException()
      : std::logic_error("Exceeded limit of class instances") {}
};

template <typename T, size_t Limit>
class ClassCounter {
 private:
  inline static size_t counter = 0;

 public:
  ClassCounter() {
    if (counter >= Limit) {
      throw InstanceLimitExceededException();
    }
    ++counter;
  }

  ClassCounter(const ClassCounter& other) = delete;
  ClassCounter& operator=(const ClassCounter& other) = delete;

  ClassCounter(ClassCounter&& other) = delete;
  ClassCounter& operator=(ClassCounter&& other) = delete;

 protected:
  ~ClassCounter() { --counter; }
};

#endif
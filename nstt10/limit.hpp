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

  static void check_and_increment() {
    if (counter >= Limit) {
      throw InstanceLimitExceededException();
    }
    ++counter;
  }

 public:
  ClassCounter() { check_and_increment(); }

  ClassCounter(const ClassCounter& other) { check_and_increment(); }
  ClassCounter& operator=(const ClassCounter& other) { return *this; }

  ClassCounter(ClassCounter&& other) { check_and_increment(); }
  ClassCounter& operator=(ClassCounter&& other) { return *this; }

 protected:
  ~ClassCounter() { --counter; }
};

#endif
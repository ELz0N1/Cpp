#include <gtest/gtest.h>

#include "limit.hpp"

class Singleton : public ClassCounter<Singleton, 1> {};
class Counter : public ClassCounter<Counter, 3> {};

TEST(ClassCounterTest, SingletonTest) {
  Singleton* first = new Singleton;
  EXPECT_THROW(Singleton second, InstanceLimitExceededException);

  delete first;
  EXPECT_NO_THROW(Singleton second);
}

TEST(ClassCounterTest, CounterTest) {
  Counter c1;
  Counter c2;
  {
    Counter c3;
  }
  Counter c3;

  EXPECT_THROW(Counter c4, InstanceLimitExceededException);
}
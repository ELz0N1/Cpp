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

TEST(ClassCounterTest, CopyConstructorTest) {
  Counter obj1;
  Counter obj2;
  Counter obj3;

  EXPECT_THROW({ Counter obj4(obj1); }, InstanceLimitExceededException);
}

TEST(ClassCounterTest, CopyAssignmentTest) {
  Counter obj1;
  Counter obj2;
  Counter obj3;

  EXPECT_NO_THROW({ obj1 = obj2; });
}

TEST(ClassCounterTest, MoveConstructorTest) {
  Counter obj1;
  Counter obj2;
  Counter obj3;

  EXPECT_THROW(
      { Counter obj4(std::move(obj1)); }, InstanceLimitExceededException);
}

TEST(ClassCounterTest, MoveAssignmentTest) {
  Counter obj1;
  Counter obj2;
  Counter obj3;

  EXPECT_NO_THROW({ obj1 = std::move(obj2); });
}

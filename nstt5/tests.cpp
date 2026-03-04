#include <gtest/gtest.h>

#include "scopedptr.hpp"

struct Counter {
  static int instances;
  int value;
  Counter(int v = 0) : value(v) { instances++; }
  Counter(const Counter& other) : value(other.value) { instances++; }
  ~Counter() { instances--; }
};
int Counter::instances = 0;

class ScopedPointerTest : public ::testing::Test {
  protected:
  void SetUp() override { Counter::instances = 0; }
};

TEST_F(ScopedPointerTest, DeepCopyCreatesNewInstance) {
  {
    DeepCopyScopedPointer<Counter> ptr1(new Counter(42));
    EXPECT_EQ(Counter::instances, 1);

    DeepCopyScopedPointer<Counter> ptr2 = ptr1;
    EXPECT_EQ(Counter::instances, 2);
    EXPECT_EQ(ptr2->value, 42);
    EXPECT_NE(&(*ptr1), &(*ptr2));
  }
  EXPECT_EQ(Counter::instances, 0);
}

TEST_F(ScopedPointerTest, DeepCopyMoveSemantics) {
  {
    DeepCopyScopedPointer<Counter> ptr1(new Counter(10));
    DeepCopyScopedPointer<Counter> ptr2 = std::move(ptr1);
    EXPECT_EQ(Counter::instances, 1);
    EXPECT_EQ(ptr2->value, 10);
  }
  EXPECT_EQ(Counter::instances, 0);
}

TEST_F(ScopedPointerTest, MoveOnlyTransferOwnership) {
  {
    MoveScopedPointer<Counter> ptr1(new Counter(100));
    EXPECT_EQ(Counter::instances, 1);

    MoveScopedPointer<Counter> ptr2 = std::move(ptr1);
    EXPECT_EQ(Counter::instances, 1);
    EXPECT_EQ(ptr2->value, 100);
  }
  EXPECT_EQ(Counter::instances, 0);
}

TEST_F(ScopedPointerTest, MoveAssignmentWorks) {
  MoveScopedPointer<Counter> ptr1(new Counter(1));
  MoveScopedPointer<Counter> ptr2(new Counter(2));

  ptr2 = std::move(ptr1);
  EXPECT_EQ(ptr2->value, 1);
  EXPECT_EQ(Counter::instances, 1);  
}
#include <gtest/gtest.h>

#include "match.hpp"

TEST(MatchTest, Test1) {
  auto is_a = [](int ch) { return ch == 'a'; };

  EXPECT_EQ(1, getIndexOfFirstMatch(is_a, 'b', 'a', 'a'));
  EXPECT_EQ(0, getIndexOfFirstMatch(is_a, 'a', 'b', 'c'));
  EXPECT_EQ(-1, getIndexOfFirstMatch(is_a, 'b', 'c', 'd'));
}

TEST(MatchTest, Test2) {
  auto checker = [](bool b) { return b; };

  EXPECT_EQ(1, getIndexOfFirstMatch(checker, false, true, false));
  EXPECT_EQ(2, getIndexOfFirstMatch(checker, false, false, true));
  EXPECT_EQ(-1, getIndexOfFirstMatch(checker, false, false, false));
}

TEST(MatchTest, Test3) {
  auto is_even = [](int n) { return n % 2 == 0; };

  EXPECT_EQ(2, getIndexOfFirstMatch(is_even, 1, 3, 6));
  EXPECT_EQ(0, getIndexOfFirstMatch(is_even, 2, 3, 4));
  EXPECT_EQ(-1, getIndexOfFirstMatch(is_even, 1, 3, 5));
}
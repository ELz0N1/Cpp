#include <gtest/gtest.h>

#include "prime.hpp"

TEST(PrimeTest, Test) {
  EXPECT_EQ(2, nth_prime_v<1>{});
  EXPECT_EQ(3, nth_prime_v<2>{});
  EXPECT_EQ(5, nth_prime_v<3>{});
  EXPECT_EQ(7, nth_prime_v<4>{});
  EXPECT_EQ(11, nth_prime_v<5>{});
  EXPECT_EQ(29, nth_prime_v<10>{});
  EXPECT_EQ(347, nth_prime_v<69>{});
}
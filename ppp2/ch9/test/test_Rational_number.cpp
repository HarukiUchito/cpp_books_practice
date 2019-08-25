#include <gtest/gtest.h>
#include <iostream>
#include <Rational_number.hpp>

TEST(RationalNumberTest, INITIALIZEATION)
{
    EXPECT_DOUBLE_EQ(0.5, Rational_number(1, 2).to_double());
    EXPECT_DOUBLE_EQ(0.3, Rational_number(3, 10).to_double());
}

TEST(RationalNumberTest, ASSIGNMENT)
{
    Rational_number r = Rational_number {1, 2};
    EXPECT_DOUBLE_EQ(0.5, r.to_double());
}

TEST(RationalNumberTest, ADDITION)
{
    Rational_number r1 {1, 2}, r2 {1, 3};
    Rational_number sum {r1 + r2};
    EXPECT_DOUBLE_EQ(5.0/6.0, sum.to_double());
}

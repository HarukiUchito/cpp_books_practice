#include <gtest/gtest.h>
#include <iostream>
#include <Rational.hpp>

TEST(RationalTest, INITIALIZEATION)
{
    EXPECT_DOUBLE_EQ(0.5, Rational(1, 2).to_double());
    EXPECT_DOUBLE_EQ(0.3, Rational(3, 10).to_double());
}

TEST(RationalTest, ASSIGNMENT)
{
    Rational r = Rational{1, 2};
    EXPECT_DOUBLE_EQ(0.5, r.to_double());
}

TEST(RationalTest, ADDITION)
{
    Rational r1{1, 2}, r2{1, 3};
    Rational sum1{r1 + r2};
    EXPECT_DOUBLE_EQ(5.0 / 6.0, sum1.to_double());

    Rational r3{1, 6}, r4{1, 3};
    Rational sum2{r3 + r4};
    EXPECT_DOUBLE_EQ(1.0 / 2.0, sum2.to_double());
}

TEST(RationalTest, SUBTRACTION)
{
    Rational r1{1, 2}, r2{1, 3};
    Rational sub1{r1 - r2};
    EXPECT_DOUBLE_EQ(1.0 / 6.0, sub1.to_double());

    Rational r3{4, 6}, r4{1, 3};
    Rational sub2{r3 - r4};
    EXPECT_DOUBLE_EQ(1.0 / 3.0, sub2.to_double());
}

TEST(RationalTest, MULTIPLICATION)
{
    Rational r1{3, 4}, r2{2, 7};
    EXPECT_DOUBLE_EQ(3.0 / 14.0, (r1 * r2).to_double());
}

TEST(RationalTest, DIVISION)
{
    Rational r1{3, 4}, r2{2, 7};
    EXPECT_DOUBLE_EQ(21.0 / 8.0, (r1 / r2).to_long_double());
}

TEST(RationalTest, NORMALIZATION)
{
    Rational r1{2, 4};
    EXPECT_EQ(1, r1.numerator());
    EXPECT_EQ(2, r1.denomerator());

    Rational r2{5, -125};
    EXPECT_EQ(-1, r2.numerator());
    EXPECT_EQ(25, r2.denomerator());
}
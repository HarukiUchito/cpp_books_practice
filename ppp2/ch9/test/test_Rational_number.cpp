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
    Rational_number r = Rational_number{1, 2};
    EXPECT_DOUBLE_EQ(0.5, r.to_double());
}

TEST(RationalNumberTest, ADDITION)
{
    Rational_number r1{1, 2}, r2{1, 3};
    Rational_number sum1{r1 + r2};
    EXPECT_DOUBLE_EQ(5.0 / 6.0, sum1.to_double());

    Rational_number r3{1, 6}, r4{1, 3};
    Rational_number sum2{r3 + r4};
    EXPECT_DOUBLE_EQ(1.0 / 2.0, sum2.to_double());
}

TEST(RationalNumberTest, SUBTRACTION)
{
    Rational_number r1{1, 2}, r2{1, 3};
    Rational_number sub1{r1 - r2};
    EXPECT_DOUBLE_EQ(1.0 / 6.0, sub1.to_double());

    Rational_number r3{4, 6}, r4{1, 3};
    Rational_number sub2{r3 - r4};
    EXPECT_DOUBLE_EQ(1.0 / 3.0, sub2.to_double());
}

TEST(RationalNumberTest, NORMALIZATION)
{
    Rational_number r1{2, 4};
    EXPECT_EQ(1, r1.numerator());
    EXPECT_EQ(2, r1.denomerator());

    Rational_number r2{5, -125};
    EXPECT_EQ(-1, r2.numerator());
    EXPECT_EQ(25, r2.denomerator());
}
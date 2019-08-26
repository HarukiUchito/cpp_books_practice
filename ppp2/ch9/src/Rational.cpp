#include "Rational.hpp"

int64_t gcd(int64_t a, int64_t b)
{
    return b ? gcd(b, a % b) : a;
}

int64_t lcm(int64_t a, int64_t b)
{
    int64_t temp = gcd(a, b);
    return temp ? (a / temp * b) : 0;
}

Rational& Rational::operator=(const Rational& r)
{
    mNumerator = r.numerator();
    mDenominator = r.denominator();
    return *this;
}

Rational& Rational::operator+=(const Rational &r)
{
    int64_t denom_lcm = lcm(mDenominator, r.denominator());
    int64_t num_sum{0};
    num_sum += denom_lcm / mDenominator * mNumerator;
    num_sum += denom_lcm / r.denominator() * r.numerator();
    mNumerator = num_sum;
    mDenominator = denom_lcm;
    return *this;
}

Rational& Rational::operator-=(const Rational &r)
{
    int64_t denom_lcm = lcm(mDenominator, r.denominator());
    int64_t num_sub{0};
    num_sub += denom_lcm / mDenominator * mNumerator;
    num_sub -= denom_lcm / r.denominator() * r.numerator();
    mNumerator = num_sub;
    mDenominator = denom_lcm;
    return *this;
}

Rational& Rational::operator*=(const Rational &r)
{
    mNumerator *= r.numerator();
    mDenominator *= r.denominator();
    return *this;
}

Rational& Rational::operator/=(const Rational &r)
{
    mNumerator *= r.denominator();
    mDenominator *= r.numerator();
    return *this;
}

Rational Rational::operator+() const
{
    return Rational{*this};
}

Rational Rational::operator-() const
{
    return Rational{-mNumerator, mDenominator};
}

void Rational::normalize()
{
    int64_t g = gcd(mDenominator, mNumerator);
    mDenominator /= g;
    mNumerator /= g;
    if (mDenominator < 0)
    {
        mDenominator *= -1;
        mNumerator *= -1;
    }
}

bool operator==(const Rational &r1, const Rational &r2)
{
    bool fn = r1.numerator() == r2.numerator();
    bool fd = r1.denominator() == r2.denominator();
    return fn and fd;
}

bool operator!=(const Rational &r1, const Rational &r2)
{
    return not (r1 == r2);
}

Rational operator+(const Rational& r1, const Rational& r2) { return Rational(r1) += r2; }
Rational operator-(const Rational& r1, const Rational& r2) { return Rational(r1) -= r2; }
Rational operator*(const Rational& r1, const Rational& r2) { return Rational(r1) *= r2; }
Rational operator/(const Rational& r1, const Rational& r2) { return Rational(r1) /= r2; }

std::ostream &operator<<(std::ostream &ofs, const Rational &r)
{
    ofs << r.numerator() << " / " << r.denominator();
    ofs << " (" << r.to_double() << ")";
    return ofs;
}
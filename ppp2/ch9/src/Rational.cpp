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

Rational Rational::operator+(Rational &r)
{
    int64_t denom_lcm = lcm(mDenominator, r.denominator());
    int64_t num_sum{0};
    num_sum += denom_lcm / mDenominator * mNumerator;
    num_sum += denom_lcm / r.denominator() * r.numerator();
    return Rational{num_sum, denom_lcm};
}

Rational Rational::operator-(Rational &r)
{
    int64_t denom_lcm = lcm(mDenominator, r.denominator());
    int64_t num_sub{0};
    num_sub += denom_lcm / mDenominator * mNumerator;
    num_sub -= denom_lcm / r.denominator() * r.numerator();
    return Rational{num_sub, denom_lcm};
}

Rational Rational::operator*(Rational &r)
{
    int64_t n = mNumerator * r.numerator();
    int64_t d = mDenominator * r.denominator();
    return Rational{n, d};
}

Rational Rational::operator/(Rational &r)
{
    int64_t n = mNumerator * r.denominator();
    int64_t d = mDenominator * r.numerator();
    return Rational{n, d};
}

bool Rational::operator==(Rational &r)
{
    bool fn = mNumerator == r.numerator();
    bool fd = mDenominator == r.denominator();
    return fn and fd;
}

bool Rational::operator!=(Rational &r)
{
    return not (*this == r);
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

std::ostream &operator<<(std::ostream &ofs, const Rational &r)
{
    ofs << r.numerator() << " / " << r.denominator();
    ofs << " (" << r.to_double() << ")";
    return ofs;
}
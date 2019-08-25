#include "Rational_number.hpp"

int64_t gcd(int64_t a, int64_t b)
{
    return b ? gcd(b, a % b) : a;
}

int64_t lcm(int64_t a, int64_t b)
{
    int64_t temp = gcd(a, b);
    return temp ? (a / temp * b) : 0;
}

Rational_number Rational_number::operator=(Rational_number &r)
{
    return Rational_number{r.numerator(), r.denomerator()};
}

Rational_number Rational_number::operator+(Rational_number &r)
{
    int64_t denom_lcm = lcm(mDenomerator, r.denomerator());
    int64_t num_sum{0};
    num_sum += denom_lcm / mDenomerator * mNumerator;
    num_sum += denom_lcm / r.denomerator() * r.numerator();
    return Rational_number{num_sum, denom_lcm};
}

Rational_number Rational_number::operator-(Rational_number &r)
{
    int64_t denom_lcm = lcm(mDenomerator, r.denomerator());
    int64_t num_sub{0};
    num_sub += denom_lcm / mDenomerator * mNumerator;
    num_sub -= denom_lcm / r.denomerator() * r.numerator();
    return Rational_number{num_sub, denom_lcm};
}

void Rational_number::normalize()
{
    int64_t g = gcd(mDenomerator, mNumerator);
    mDenomerator /= g;
    mNumerator /= g;
    if (mDenomerator < 0)
    {
        mDenomerator *= -1;
        mNumerator *= -1;
    }
}

std::ostream &operator<<(std::ostream &ofs, const Rational_number &r)
{
    ofs << r.numerator() << " / " << r.denomerator();
    ofs << " (" << r.to_double() << ")";
    return ofs;
}
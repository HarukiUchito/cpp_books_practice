#include "Rational_number.hpp"

llint gcd(llint a, llint b)
{
    return b ? gcd(b, a % b) : a;
}

llint lcm(llint a, llint b)
{
    llint temp = gcd(a, b);
    return temp ? (a / temp * b) : 0;
}

Rational_number Rational_number::operator=(Rational_number &r)
{
    return Rational_number{r.numerator(), r.denomerator()};
}

Rational_number Rational_number::operator+(Rational_number &r)
{
    llint denom_lcm = lcm(mDenomerator, r.denomerator());
    llint num_sum{0};
    num_sum += denom_lcm / mDenomerator * mNumerator;
    num_sum += denom_lcm / r.denomerator() * r.numerator();
    return Rational_number{num_sum, denom_lcm};
}

std::ostream &operator<<(std::ostream &ofs, const Rational_number &r)
{
    ofs << r.numerator() << " / " << r.denomerator();
    ofs << " (" << r.to_double() << ")";
    return ofs;
}
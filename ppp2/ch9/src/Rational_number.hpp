#ifndef RATIONAL_NUMBER_HPP
#define RATIONAL_NUMBER_HPP

#include <iostream>

using llint = long long int;

// Mathematical utility functions
llint gcd(llint a, llint b);
llint lcm(llint a, llint b);

class Rational_number
{
public:
    Rational_number() {}
    Rational_number(llint numerator, llint denomerator)
        : mNumerator(numerator), mDenomerator(denomerator) {}
    Rational_number(const Rational_number &r)
        : mNumerator(r.numerator()), mDenomerator(r.denomerator()) {}

    inline double to_double() const;
    inline llint numerator() const;
    inline llint denomerator() const;

    Rational_number operator=(Rational_number &r);
    Rational_number operator+(Rational_number &r);

private:
    // mNumerator / mDenomerator
    llint mNumerator{0};
    llint mDenomerator{1};
};

std::ostream &operator<<(std::ostream &ofs, const Rational_number &r);

double Rational_number::to_double() const
{
    return double(mNumerator) / double(mDenomerator);
}

llint Rational_number::numerator() const
{
    return mNumerator;
}

llint Rational_number::denomerator() const
{
    return mDenomerator;
}

#endif
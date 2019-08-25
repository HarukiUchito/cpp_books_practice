#ifndef RATIONAL_NUMBER_HPP
#define RATIONAL_NUMBER_HPP

#include <iostream>

// Mathematical utility functions
int64_t gcd(int64_t a, int64_t b);
int64_t lcm(int64_t a, int64_t b);

class Rational_number
{
public:
    Rational_number() {}
    Rational_number(const int64_t numerator, const int64_t denomerator)
        : mNumerator(numerator), mDenomerator(denomerator) {}
    Rational_number(const Rational_number &r)
        : mNumerator(r.numerator()), mDenomerator(r.denomerator()) {}

    inline double to_double() const;
    inline int64_t numerator() const;
    inline int64_t denomerator() const;

    Rational_number operator=(Rational_number &r);
    Rational_number operator+(Rational_number &r);

private:
    // mNumerator / mDenomerator
    int64_t mNumerator{0};
    int64_t mDenomerator{1};
};

std::ostream &operator<<(std::ostream &ofs, const Rational_number &r);

double Rational_number::to_double() const
{
    return double(mNumerator) / double(mDenomerator);
}

int64_t Rational_number::numerator() const
{
    return mNumerator;
}

int64_t Rational_number::denomerator() const
{
    return mDenomerator;
}

#endif
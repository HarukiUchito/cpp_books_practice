#ifndef Rational_HPP
#define Rational_HPP

#include <iostream>

// Mathematical utility functions
int64_t gcd(int64_t a, int64_t b);
int64_t lcm(int64_t a, int64_t b);

// Rational Number Expression
class Rational
{
public:
    Rational() {}
    Rational(const int64_t numerator, const int64_t denomerator)
        : mNumerator(numerator), mDenomerator(denomerator)
    {
        normalize();
    }
    Rational(const Rational &r)
        : mNumerator(r.numerator()), mDenomerator(r.denomerator())
    {
        normalize();
    }

    inline double to_double() const;
    inline int64_t numerator() const;
    inline int64_t denomerator() const;

    Rational operator=(Rational &r);
    Rational operator+(Rational &r);
    Rational operator-(Rational &r);
private:
    // mNumerator / mDenomerator
    int64_t mNumerator{0};
    int64_t mDenomerator{1};

    // Reduction of fraction
    // and if the denomerator is less than 0
    // multiplies -1 to both  
    void normalize();
};

// output Rational number in following format
// n / d (f) 
std::ostream &operator<<(std::ostream &ofs, const Rational &r);

double Rational::to_double() const
{
    return double(mNumerator) / double(mDenomerator);
}

int64_t Rational::numerator() const
{
    return mNumerator;
}

int64_t Rational::denomerator() const
{
    return mDenomerator;
}

#endif
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
    Rational(const int64_t numerator, const int64_t denominator)
        : mNumerator(numerator), mDenominator(denominator)
    {
        normalize();
    }
    Rational(const Rational &r)
        : mNumerator(r.numerator()), mDenominator(r.denominator())
    {
        normalize();
    }

    inline double to_double() const;
    inline long double to_long_double() const;
    inline int64_t numerator() const;
    inline int64_t denominator() const;

    Rational& operator=(const Rational& r);

    // compound assignment operators
    Rational& operator+=(const Rational &r);
    Rational& operator-=(const Rational &r);
    Rational& operator*=(const Rational &r);
    Rational& operator/=(const Rational &r);
private:
    // mNumerator / mDenominator
    int64_t mNumerator{0};
    int64_t mDenominator{1};

    // Reduction of fraction
    // and if the denominator is less than 0
    // multiplies -1 to both  
    void normalize();
};

bool operator==(Rational &r1, Rational &r2);
bool operator!=(Rational &r1, Rational &r2);

// Following operators are defined using compound assignment operators
Rational operator+(const Rational& r1, const Rational& r2);
Rational operator-(const Rational& r1, const Rational& r2);
Rational operator*(const Rational& r1, const Rational& r2);
Rational operator/(const Rational& r1, const Rational& r2);

// output Rational number in following format
// n / d (f) 
std::ostream &operator<<(std::ostream &ofs, const Rational &r);

double Rational::to_double() const
{
    return double(mNumerator) / double(mDenominator);
}

long double Rational::to_long_double() const
{
    return (long double)mNumerator / (long double)mDenominator;
}

int64_t Rational::numerator() const
{
    return mNumerator;
}

int64_t Rational::denominator() const
{
    return mDenominator;
}

#endif
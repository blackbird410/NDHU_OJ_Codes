#include<iostream>
// #include "Fraction.h"
using namespace std;

int gcd(int a, int b) {
  return (b) ? gcd(b, a % b) : a; 
}

int lcm(int n, int m)
{
  return (n / gcd(n, m)) * m; 
}

Fraction simplify( Fraction &f ) 
{
  // Find the greatest common divisor between the numerator and the denominator
  int n = f.getNumerator();
  int d = f.getDenominator();
  int g = gcd(n, d);
  if (g) 
  {
    f.setNumerator( n / g );
    f.setDenominator( d / g );
  } else 
    f.setDenominator(1);

  return f;
}

Fraction operator+(const Fraction &first, const Fraction &second ) 
{
  int denominator = lcm(first.getDenominator(), second.getDenominator());
  int numerator = ( first.getNumerator() * (denominator / first.getDenominator()) ) 
    + ( second.getNumerator() * (denominator / second.getDenominator()) );

  return Fraction( numerator, denominator );
} 

Fraction operator-(const Fraction &first, const Fraction &second )
{
  Fraction negativeF(- (second.getNumerator()), second.getDenominator());

  return ( first + negativeF );
}

bool operator==( const Fraction &first, const Fraction &second )
{
  Fraction copyFirst(first.getNumerator(), first.getDenominator());
  Fraction copySecond(second.getNumerator(), second.getDenominator());

  simplify(copyFirst);
  simplify(copySecond);

  return ( (copyFirst.getNumerator() == copySecond.getNumerator()) 
  && (copyFirst.getDenominator() == copySecond.getDenominator()) );
}

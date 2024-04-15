#include<iostream>
#include "Fraction.h"
using namespace std;

int gcd(int a, int b) {
  return (b) ? gcd(b, a % b) : a; 
}

int lcm(int n, int m)
{
  return (n / gcd(n, m)) * m; 
}

const Fraction simplify( Fraction &f ) 
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

const Fraction operator+(const Fraction &first, const Fraction &second ) 
{
  int denominator = lcm(first.getDenominator(), second.getDenominator());
  int numerator = ( first.getNumerator() * (denominator / first.getDenominator()) ) 
    + ( second.getNumerator() * (denominator / second.getDenominator()) );

  Fraction result( numerator, denominator );
  simplify(result);

  return result;
} 

const Fraction operator-(const Fraction &first, const Fraction &second )
{
  Fraction negativeF(- (second.getNumerator()), second.getDenominator());

  return ( first + negativeF );
}

// const Fraction &operator=( Fraction &left, const Fraction &right )
// {
//   left.setNumerator( right.getNumerator() );
//   left.setDenominator( right.getDenominator() );
//   simplify( left );
//
//   return left;
// }


bool operator==( const Fraction &first, const Fraction &second )
{
  Fraction copyFirst(first.getNumerator(), first.getDenominator());
  Fraction copySecond(second.getNumerator(), second.getDenominator());

  simplify(copyFirst);
  simplify(copySecond);

  return ( (copyFirst.getNumerator() == copySecond.getNumerator()) && (copyFirst.getDenominator() == copySecond.getDenominator()) );
}

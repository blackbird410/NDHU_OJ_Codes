#include <iostream>
using namespace std;

class Fraction {
public:
  Fraction() : numerator(0), denominator(1) {}
  Fraction(int n, int m) : numerator(n) 
  {
    if(m == 0)
      throw "divided by zero";
    denominator = m;
    simplify();
  }

  int getNumerator() const { return numerator; }
  int getDenominator() const { return denominator;  }
  void setNumerator(int n) { numerator = n; }
  void setDenominator(int m) 
  {    
    if(m == 0)
      throw "divided by zero";
    denominator = m;
  }
  int gcd(int a, int b) {
    return (b) ? gcd(b, a % b) : a; 
  }

  int lcm(int n, int m)
  {
    return (n / gcd(n, m)) * m; 
  }

  Fraction simplify() 
  {
    int n = getNumerator();
    int d = getDenominator();
    int g = gcd(n, d);
    if (g) 
    {
      setNumerator( n / g );
      setDenominator( d / g );
    } else 
      setDenominator(1);

    return *this;
  }

  Fraction operator+( const Fraction &second ) 
  {
    int denominator = getDenominator() * second.getDenominator();
    int numerator = ( getNumerator() * (denominator / getDenominator()) ) 
      + ( second.getNumerator() * (denominator / second.getDenominator()) );

    return Fraction( numerator, denominator );
  } 

  Fraction operator-( const Fraction &second )
  {
    Fraction negativeF(- (second.getNumerator()), second.getDenominator());
    return ( *this + negativeF );
  }

  Fraction operator*(const Fraction &b) {
    return Fraction(getNumerator() * b.getNumerator(), getDenominator() * b.getDenominator());
  }

  Fraction operator/( const Fraction &b ) {
    return Fraction(getNumerator() * b.getDenominator(), getDenominator() * b.getNumerator());
  }

  Fraction operator!()
  {
    return Fraction(denominator, numerator);
  }

  Fraction &operator=( const Fraction &right )
  {
    return Fraction( right.getNumerator(), right.getDenominator() );
  }

  void display() {
    if (denominator != 1)
    	cout << "(" << numerator << "/" << denominator << ")" << endl;
    else
      cout << "(" << numerator << ")" << endl;
  }

  friend std::ostream& operator << (std::ostream& out, const Fraction &f) 
  {
    if (f.denominator != 1)
    	out << "(" << f.numerator << "/" << f.denominator << ")" << endl;
    else
        out << "(" << f.numerator << ")" << endl;
    return out;
  }
private:
  int numerator, denominator;
};


int main()
{
  Fraction l[5] = {Fraction(1, 2), Fraction(2, 3), Fraction(3, 4), Fraction(4, 5), Fraction(5, 6)};

  Fraction a, b, c, d, e, f;
  b = l[0];
  c = l[1];
  d = l[2];
  e = l[3];
  f = l[4];
  a = (((b + c) - d) * e) / f;
  cout << a;
  cout << !a;

  return 0;
}

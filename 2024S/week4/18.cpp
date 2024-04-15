#include <iostream>
using namespace std;

class Fraction {
public:
  Fraction() : numerator(0), denominator(1) {}
  Fraction(int n, int m) : numerator(n) {
    if(m == 0)
      throw "divided by zero";
    denominator = m;
  }

  Fraction operator=(const Fraction &b) {
    setNumerator(b.getNumerator());
    setDenominator(b.getDenominator());
    reduce();

    return *this;
  }

  Fraction operator+(const Fraction &b) {
    Fraction result;
    int d = getDenominator() * b.getDenominator();

    result.setDenominator(d);
    result.setNumerator((d / getDenominator()) * getNumerator() + (d / b.getDenominator()) * b.getNumerator());
    result.reduce();

    return result;
  }

  Fraction operator-(const Fraction &b) {
    Fraction result;
    int d = getDenominator() * b.getDenominator();

    result.setDenominator(d);
    result.setNumerator((d / getDenominator()) * getNumerator() - (d / b.getDenominator()) * b.getNumerator());
    result.reduce();

    return result;
  }

  Fraction operator*(const Fraction &b) {
    Fraction result;

    result.setDenominator(getDenominator() * b.getDenominator());
    result.setNumerator(getNumerator() * b.getNumerator());
    result.reduce();

    return result;
  }

  Fraction operator/(const Fraction &b) {
    Fraction reverse(b.getDenominator(), b.getNumerator());
    Fraction result;

    result.setDenominator(getDenominator() * reverse.getDenominator());
    result.setNumerator(getNumerator() * reverse.getNumerator());
    result.reduce();

    return result;
  }

  bool operator==(Fraction &b) {
    b.reduce();
    reduce();

    return (getNumerator() == b.getNumerator() && getDenominator() == b.getDenominator());
  }

  void reduce() {
    int n = getNumerator();
    int d = getDenominator();
    int g = gcd(abs(n), abs(d));

    if (g > 1) {
      if ((n < 0  && d > 0) || (n > 0 && d < 0)) {
        setNumerator(-abs(n) / g);
        setDenominator(abs(d) / g);
      } else {
        setNumerator(abs(n) / g);
        setDenominator(abs(d) / g);
      }
      
    } else if (!g)
      setDenominator(1);
  }

  int getNumerator() const {
    return numerator;
  }
  int getDenominator() const {
    return denominator;
  }
  void setNumerator(int n) {
    numerator = n;
  }
  void setDenominator(int m) {
    if(m == 0)
      throw "divided by zero";
    denominator = m;
  }

  void display() {
    if (denominator != 1)
    	cout << "(" << numerator << "/" << denominator << ")" << endl;
    else
        cout << numerator << endl;
  }

  int gcd(int m, int n)
  {
    // Euclid GCD
    if (n == 0)
      return 0;
    else if (m == n)
      return m;
    else
    {
      if (m < n)
      {
        m += n;
        n = m - n;
        m -= n;
      }

      m -= n;

      if (m > n)
        return gcd(m, n);
      else
        return gcd(n, m);
    }
  }

  friend std::ostream& operator << (std::ostream& out, const Fraction &f) {
    if (f.denominator != 1)
    	out << "(" << f.numerator << "/" << f.denominator << ")" << endl;
    else
        out << f.numerator << endl;
    return out;
  }
private:
  int numerator, denominator;
};


int main()
{
  Fraction l[5] = {Fraction(1, 2), Fraction(2, 3), Fraction(3, 4), Fraction(4, 5), Fraction(5, 6)};
  //int i = -1;
  //int n = 0, d = 0;

  //while (++i < 5) {
    //cin >> n >> d;
    //l[i].setNumerator(n);
    //l[i].setDenominator(d);
  //}

  Fraction a, b, c, d, e, f;
  b = l[0];
  c = l[1];
  d = l[2];
  e = l[3];
  f = l[4];
  a = (((b + c) - d) * e) / f;
  cout << a;

  return 0;
}

#include <iostream>
#include <time.h>
#include <cstdlib>
#include <string>
using namespace std;

#define ASCII_N_LOWBOUND 48
#define SIZE 1000

class Digit { // class Digit represent a digit in base 10
  int digit;
public:
  Digit () : digit(0) {};
  Digit(int d) : digit(d % 10) {}
  void setDigit(int d) { digit = d % 10; }
  int getDigit() const {return digit;}
};

class Integer { //class Integer represent a poistive integer
  Digit value[SIZE];
  int length;
  bool sign;
public:
  //construct an integer in base 10 using a string.
  //This constructor will convert the given string to integer if possible.
  //Otherwise it will convert the digit part in prefix of the given string.
  Integer(string n) {
    int i = 0, j = 0;
    bool numberFound = false;

    while (n[i] != '\0' && n[i] >= ASCII_N_LOWBOUND && n[i] < ASCII_N_LOWBOUND + 10) {
      if(n[i]) numberFound = true;
      if (numberFound) {
        value[j].setDigit(n[i] - ASCII_N_LOWBOUND);
        j++;
      }
      i++;
    }
    length = j;
    sign = false;
  }
  //default constructor will construct an Integer object with value 0.
  Integer() {
    for (int i = 0; i < SIZE; i++) 
      value[i].setDigit(0);
    length = 0;
    sign = false;
  };

  Integer operator=(Integer _other) {
    int i;
    int _otherLength = _other.getLength();
    for (i = 0; i < _otherLength; i++) 
      value[i].setDigit(_other.value[i].getDigit());
    this->updateLength(_otherLength);
    this->sign = _other.sign;

    return *this;
  };
  
  Integer operator+(Integer& b) {
    int i = length - 1, j = b.length - 1, v = 0, carry = 0;
    int maxLen = (i > j) ? i + 1 : j + 1;
    string holder = "";

    // TODO: Fix the carry problem here
    while(--maxLen >= 0) {
      if (i < 0) 
        v = b.value[j].getDigit() + carry;
      else if (j < 0) 
        v = value[i].getDigit() + carry;
      else 
        v = value[i].getDigit() + b.value[j].getDigit() + carry;
      holder = to_string(v % 10) + holder;
      carry = v / 10;
      i--;
      j--;
    }

    if (carry) holder = to_string(carry) + holder;
    //else if (carry) {
      //string s = "";
      //char firstDigit = holder[0];
      //for (i = 1; i < holder.length(); i++) s += holder[i];

      //holder = to_string(carry + (firstDigit - '0')) + s;
    //}
    Integer result(holder);
    return result;
  }

  Integer operator-(Integer& b) {
    int i = length - 1, j = b.length - 1, v = 0, borrow = 0;
    int maxLen = (i > j) ? i + 1 : j + 1;
    Integer diff("0");

    if (this->sign == b.sign) {
      diff = absDiff(*this, b);
      int bigger = absComp(*this, b);
      if (!bigger) return diff;

      if (this->sign) diff.sign = (bigger == -1);
      else diff.sign = (bigger == 1);
    } else {
      // Different signs
      diff = *this + b;
      diff.sign = this->sign;
    }

    format(diff);
    return diff;
  }
  
  void format(Integer &r) {
    int i = 0;
    int l = r.getLength();
    string s = "";

    bool valid = false;
    for (i = 0; i < l; i++) {
      if (r.value[i].getDigit()) valid = true;

      if (valid) s += to_string(r.value[i].getDigit());
    }

    Integer t(s);
    t.sign = r.getSign();
    r = t;
  }

  Integer absDiff(Integer& a , Integer& b) {
    Integer diff("0");
    int i = a.length - 1, j = b.length - 1, v = 0, borrow = 0;
    int maxLen = (i > j) ? i + 1 : j + 1;
    string holder = "";
    int c = absComp(a, b);

    if (!c) return diff;

    if (c == -1) {
      while (--maxLen >= 0) {
        if (j < 0) {
          if (a.value[i].getDigit() < borrow) {
            holder = to_string(a.value[i].getDigit() + 10 - borrow) + holder;
            borrow = 1;
          } else {
            holder = to_string(a.value[i].getDigit() - borrow) + holder;
            borrow = 0;
          }
        } else {
          if (a.value[i].getDigit() < b.value[j].getDigit() + borrow) {
            holder = to_string(a.value[i].getDigit() + 10 - borrow - b.value[j].getDigit()) + holder;
            borrow = 1;
          } else {
            holder = to_string(a.value[i].getDigit() - borrow - b.value[j].getDigit()) + holder;
            borrow = 0;
          }
        }
        j--;
        i--;
      }
      if (borrow) holder = to_string(borrow) + holder;

    } else 
      return absDiff(b, a);
    
    diff = Integer(holder);
    return diff;
  }

  int absComp(Integer &a, Integer &b) {
    if (a.length > b.length) 
      return -1;
    else if (a.length < b.length)
      return 1;
    else {
      // Compare every digit until you find which has the first bigger digit
      int i = 0;
      while(i < a.length) {
        if (a.value[i].getDigit() > b.value[i].getDigit())
          return -1;
        else if (a.value[i].getDigit() < b.value[i].getDigit()) 
          return 1;
        i++;
      }
      return 0;
    }
  }

  Integer addition(Integer &b) {
    Integer result;
    if (sign == b.sign) {
      result = *this + b;
      result.sign = sign;
    } else if (length > b.length) {
      if (sign && !b.sign) {
        result = *this - b;
        result.sign = true;
      } else {
        result = *this - b;
        result.sign = false;
      }
    } else {
      if (sign && !b.sign) {
        result = b - *this;
        result.sign = false;
      } else {
        result = b - *this;
        result.sign = true;
    }
    }

    return result;
  }

    //function subtraction will minus b from current object and return a new Integer object as result.
  Integer subtraction(Integer &b) {
    return *this - b;
  }

  int getLength() {return length;}

  bool getSign() {return sign;}

  void updateLength(int newLength) {
    length = newLength;
  }

  void updateLength() {
    length += 1;
  }

  void nextDigit(int v) {
    value[length].setDigit(v);
    length++;
  }

  void display() {
    int i = 0;
    int l = getLength();
    if (getSign()) cout << "-";
    for (i = 0; i < l; i++) cout << value[i].getDigit();
  }

  //Display the value in given base from 2 to 16.
  //Order of symbol as 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F.
  string displayInBase(int base) {
    int i = 0, iR = 0;
    int dec = 0, r = 0, dL, digitCollected;
    Integer dividend;
    Integer quotient;
    char remainder[SIZE];

    // Create an integer copy of the value that will change as we will divide it
    dividend = *this;

    // Convert the decimal number in the base specified
    do {
      dL = dividend.getLength();

      r = 0;
      i = 0;

      while(i < dL) {
        // Find part of the dividend big enough than the base
        dec = r;
        digitCollected = 0;
        while(dec < base && i < dL) {
          dec = dec * 10 + dividend.value[i].getDigit();
          i++;
          digitCollected++;
          if (digitCollected > 1 && quotient.getLength())
            quotient.nextDigit(0);
        }

        r = dec % base;
        quotient.nextDigit(dec / base);
      }

      // Save the last remainder and replace the dividend with the quotient
      remainder[iR] = (r > 9) ? r + '7' : r + '0';
      iR++;
      dividend = quotient;
      quotient.updateLength(0);
    } while(dividend.value[0].getDigit());

    // Display the digits in reverse Order
    string s = "";
    for (i = iR - 1; i >= 0; i--) 
      s += to_string(remainder[i]);
    cout << s << endl;

    return s;
  }

  string itoa() {
    string s;
    for (int i = 0; i < getLength(); i++) s += to_string(value[i].getDigit());
    if (getSign()) s = "-" + s;
    return s;
  }
};


void test() {
  int max = 10000;
  int failed = 0;

  srand(time(0));
  for (int i = 0; i < max; i++) {
    int a = rand() % 10000;
    int b = rand() % 10000;

    Integer num1(to_string(a));
    Integer num2(to_string(b));

    Integer result = num1 + num2;

    if (result.itoa() != to_string(a + b)) {
      cout << "Test failed: " << a << " + " << b << " = " << a + b << " != " << result.itoa() << endl;
      failed++;
    }
    
    result = num1 - num2;

    if (result.itoa() != to_string(a - b)) {
      cout << "Test failed: " << a << " - " << b << " = " << a - b << " != " << result.itoa() << endl;
      failed++;
    }
  }

  string outcome = (failed) ? to_string(failed) + " test(s) failed." : "All tests passed";
  cout << outcome << endl;
}

int main()
{
  string a, b;
  cin >> a >> b;
  Integer num1(a), num2(b);
  num1.addition(num2).display();
  cout << endl;
  num2.addition(num1).display();
  cout << endl;
  num1.subtraction(num2).display();
  cout << endl;
  num2.subtraction(num1).display();
  cout << endl;
  
  //test();
  return 0;
}

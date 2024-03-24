#include <iostream>
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
  }
  //default constructor will construct an Integer object with value 0.
  Integer() {
    for (int i = 0; i < SIZE; i++) 
      value[i].setDigit(0);
    length = 0;
  };

  Integer operator=(Integer _other) {
    int i;
    int _otherLength = _other.getLength();
    for (i = 0; i < _otherLength; i++) 
      value[i].setDigit(_other.value[i].getDigit());
    this->updateLength(_otherLength);
    this->sign = _other.sign;

    return *this;
  }
  
  Integer operator+(const Integer& b) const {
    int i = length - 1, j = b.length - 1, v = 0, carry = 0;
    int maxLen = (i > j) ? i + 1 : j + 1;
    Integer result;

    while(--maxLen >= 0) {
      if (i < 0) {
        result.value[maxLen].setDigit(b.value[j].getDigit() + carry);
        carry = 0;
      } else if (j < 0) {
        result.value[maxLen].setDigit(value[i].getDigit() + carry);
        carry = 0;
      } else {
        v = value[i].getDigit() + b.value[j].getDigit() + carry;
        result.value[maxLen].setDigit(v);
        carry = v / 10;
      }
      i--;
      j--;
      result.updateLength();
    }
    return result;
  }

  Integer operator-(const Integer& b) const {
    int i = length - 1, j = b.length - 1, v = 0, borrow = 0;
    int maxLen = (i > j) ? i + 1 : j + 1;
    Integer result;

    while(--maxLen >= 0) {
      if (j < 0) {
        if (value[i].getDigit() < borrow) {
          result.value[maxLen].setDigit(value[i].getDigit() + 10 - borrow);
          borrow = 1;
        } else {
          result.value[maxLen].setDigit(value[i].getDigit() - borrow);
          borrow = 0;
        }
      } else {
        if (value[i].getDigit() < b.value[j].getDigit() + borrow) {
          result.value[maxLen].setDigit(value[i].getDigit() + 10 - b.value[j].getDigit() - borrow);
          borrow = 1;
        } else {
          result.value[maxLen].setDigit(value[i].getDigit() - b.value[j].getDigit() - borrow);
          borrow = 0;
        }
      }
      i--;
      j--;
      result.updateLength();
    } 
    return result;
  }
  Integer addition(const Integer &b) const {
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

    return result;
  };
    //function subtraction will minus b from current object and return a new Integer object as result.
  Integer subtraction(const Integer &b) const {
    Integer result;
    if (!sign && !b.sign) {
      // Positive numbers
      if (this.length > b.length) {
        result = *this - b;
        result.sign = sign;
      } else if (this.length < b.lengh) {
        result
      }

    }
  }

  int getLength() {
    return length;
  }

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

  //Display the value in given base from 2 to 16.
  //Order of symbol as 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F.
  void displayInBase(int base) {
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
    for (i = iR - 1; i >= 0; i--) 
      cout << remainder[i];
  }
};

int main()
{
  string in;
  cin >> in;
  Integer i(in);
  cin >> in;
  Integer j(in);
  Integer r;
  r = i + j;
  r.displayInBase(10);
  cout << endl;
  r = i - j;
  r.displayInBase(10);
  cout << endl;
  return 0;
}

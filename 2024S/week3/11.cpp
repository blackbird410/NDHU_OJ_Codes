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

    return *this;
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
  int j;
  cin >> in;
  Integer i(in);
  for(j = 2;j <= 16; j++) {
    i.displayInBase(j);
    cout << endl;
  }
}

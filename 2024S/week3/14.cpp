#include <iostream>
#include <string>
using namespace std;

//The "reverse and add" method is simple: 
//  choose a number, 
//  reverse its digits
//  add it to the original. 
// If the sum is not a palindrome which means:
//  - it is not the same from left to right and right to left 
//  repeat this procedure.

#define SIZE 100

class Number {
  string value;
public:
  Number () : value("") {};
  Number(string d) : value(d) {};
  
  Number operator+(Number b) {
    Number result(to_string(stoi() + b.stoi()));
    return result;
  }

  Number operator=(const Number& b) {
    value = b.value;
    return *this;
  }

  void setValue(string n) {value = n;}

  string reverse() {
    string r = "";
    int l = this->value.length();
    int i = -1;
    while(--l >= 0) 
      r += value[l];
    return r;
  }

  int stoi() {
    int i = 0, l = value.length();
    int d = 0;
    for (i = 0; i < l; i++) 
      d = 10 * d + (value[i] - '0'); 
    return d;
  }

  void getPalindrome() {
    int i = 0; 
    do {
      *this = *this + Number(this->reverse());
      i++;
    } while (!isPalindrome());
    cout << i << " " << value << endl;
  }

  bool isPalindrome() {
    return value == reverse();
  }
};

int main (int argc, char *argv[]) {
  int testCases;
  cin >> testCases;
  Number n;
  string in;

  while (--testCases + 1) {
    cin >> in;
    n.setValue(in);
    n.getPalindrome();
  } 

  return 0;
}

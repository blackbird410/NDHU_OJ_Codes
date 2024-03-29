#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;

class Anagram : public string {
  string value;
  string orderedLetters;
public:
  Anagram (string s) : value(s) {
    orderedLetters = getLetters(s);
  };
  bool operator==(Anagram &str) {
    return orderedLetters == str.orderedLetters;
  };

  string getValue() {return value;}

  string getLetters(string value) {
    int i = -1;
    int length = value.length();
    string letters;
    char c;

    while (++i < length) {
      c = tolower(value[i]);
      if (c >= 'a' && c <= 'z') 
        letters += c;
    }

    sort(letters);
    return letters;
  } 

  string getLetters() {
    return orderedLetters;
  }

  void sort(string& s) {
    bool swapped = false;
    int i = 0, l = s.length();

    do {
      swapped = false;
      for (i = 0; i < l - 1; i++) {
        if (s[i] > s[i+1]) {
          s[i] += s[i+1];
          s[i + 1] = s[i] - s[i + 1];
          s[i] -= s[i + 1];
          swapped = true;
        }
      }
    } while(swapped);

  }
  
};

int main() {
  string buf;
  getline(cin, buf);
  Anagram a1(buf);
  getline(cin, buf);
  Anagram a2(buf);
  cout << (a1 == a2) << endl;
  cout << (a2 == a1) << endl;
}

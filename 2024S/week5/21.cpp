#include <iostream>
#include <string>
#include <string.h>

class Time {
  std::string time;
  int h, m, s;
public: 
  Time() : time("00:00:00"), h(0), m(0), s(0) {};
  Time(std::string t) : time(t) {
    getParams(t);
  };

  std::string toString() {return time;}

  std::string format(int n) {
    return (n < 10) ? "0" + std::to_string(n) : std::to_string(n);
  }

  int operator-( const Time &t ) {
    int a = convert(*this);
    int b = convert(t);
    return abs(convert(*this) - convert(t));
  }

  void getParams( std::string t ) {
    int i;
    char str[20];
    for (i = 0; i < t.length() && i < 20; i++) str[i] = t[i];
    str[i] = '\0'; 
    std::string temp;

    temp = strtok(str, ":");
    h = stoi(temp);
    temp = strtok(NULL, ":");
    m = stoi(temp);
    temp = strtok(NULL, ":");
    s = stoi(temp);
  }

  int convert(const Time &t) {
    // Convert time format to seconds
    return t.h * 3600 + t.m * 60 + t.s;
  }

  friend std::ostream& operator << (std::ostream& out, Time &t) {
    out << t.time;
    return out;
  }
};

int main() {
  std::string s1, s2;
  std::cin >> s1 >> s2;
  
  Time t1(s1);
  Time t2(s2);
  
  std::cout << (t2 - t1) << std::endl;
  std::cout << t1.toString() << std::endl;
  
  return 0;
}

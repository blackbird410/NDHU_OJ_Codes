#include <iostream>
#include <string>
#include <cstring>

class Date 
{
private:
  int day, month, year;
public:
  Date(int d = 1, int m = 1, int y = 1900)
  {
    setYear(y);
    setMonth(m);
    setDay(d);
  };
  Date(std::string s) { getParams(s); };
  ~Date() {};
  void setDay( int d ) 
  {
    int mDays = getMonthDays(month, year);
    day = !( d > mDays || d <= 0 ) 
      ? d : throw std::out_of_range("Day value out of range.");
  };

  void setMonth( int m ) 
  {
    month = ( m > 0 && m < 13 ) 
      ? m : throw std::out_of_range("Month value out of range.");
  };

  void setYear( int y )
  {
    year = ( y >= 1900 ) 
      ? y : throw std::out_of_range("Year value must be at least 1900");
  };

  int getDay() { return day; };
  int getMonth() { return month; };
  int getYear() { return year; };

  std::string toString() const 
  {
    std::string dateStr = std::to_string(year);
    dateStr += ( month < 10 ) ? "/0" + std::to_string(month) : "/" + std::to_string(month);
    dateStr += ( day < 10 ) ? "/0" + std::to_string(day) : "/" + std::to_string(day);

    return dateStr;
  }

  int daysBeforeDate()
  {
    int days = 0;
    for ( size_t y = 1900; y < year; ++y )
      days += 365 + isLeapYear(y);

    for (size_t m = 1; m < month; ++m)
      days += getMonthDays(m, year);

    return days + day;
  };

  int getMonthDays(int m, int year) {
    if (m == 2)
      return 28 + isLeapYear(year);
    return 30 + ((m <= 7 && (m % 2)) || (m > 7  && m % 2 == 0));
  };

  void getParams(std::string d) 
  {
    int i;
    char str[12];
    for(i = 0; i < d.length() && i < 12; i++) str[i] = d[i];
    str[i] = '\0';

    setYear(std::stoi(strtok(str, "/")));
    setMonth(std::stoi(strtok(NULL, "/")));
    setDay(std::stoi(strtok(NULL, "/")));
  };

  bool isLeapYear(int n) {
    return (n % 400 == 0 || n % 100 && n % 4 == 0);
  }

  int operator-( Date& other )
  {
    return abs(daysBeforeDate() - other.daysBeforeDate());
  }

  friend std::istream &operator>>( std::istream &input, Date &d )
  {
    std::string s;
    input >> s;
    d = Date(s);

    return input;
  }
};

int main() 
{
  Date d1, d2;

  std::cin >> d1 >> d2;
  std::cout << (d2 - d1) << std::endl;

  return 0;
}


#include <iostream>
#include "DateTime.h"

class DateTime : public Time, public Date 
{
private:
  std::string dateTime;
public:
  DateTime() : Date("1900/01/01"), Time("00:00:00") {};
  DateTime(std::string _dateTime) 
    : Date(_dateTime.substr(0, 10)), 
      Time(_dateTime.substr(11)) 
  {};

  std::string toString() 
  {
    return Date::toString() + " " + Time::toString();
  }

  friend std::istream &operator>>( std::istream& input, DateTime &d )
  {
    std::string date, time;
    input >> date >> time;
    date += " " + time;

    d = DateTime(date);

    return input;
  }
};

int main() 
{
  DateTime d;

  for( size_t i = 0; i < 2; ++i)
  {
    std::cin >> d;
    std::cout << d.toString() << std::endl;
  }

  return 0;
}


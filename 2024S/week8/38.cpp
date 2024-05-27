#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <fstream>

// Two DateRange A and B overlap if:
// - (A.start < B.start && B.start < A.end || B.start < A.start && A.start < B.end)

int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Date {
public:
  int day, month, year;
  Date() {};
  Date(std::string date) { parseDate(date); };
  Date(const Date& other) : day(other.day), month(other.month), year(other.year) {};

  void parseDate(std::string date) {
    sscanf(date.c_str(), "%4d%2d%2d", &year, &month, &day);
  };

  bool isLeapYear() {
    return (year % 400 == 0 || year % 100 && year % 4 == 0);
  };

  Date nextDay() const {
    Date next = *this;

    next.day++;
    if (next.day > days_in_month[next.month]) {
      next.day = (next.month == 2 && next.isLeapYear()) ? 29 : 1;
      next.month++;

      if (next.month > 12) {
        next.month = 1;
        next.year++;
      }
    }
    return next;
  }

  Date previousDay() const {
    Date previous = *this;

    previous.day--;
    if (!previous.day) {
      previous.month--;
      if (!previous.month) {
        previous.year--;
        previous.month = 12;
      } 
      previous.day = (previous.month == 2) ? days_in_month[previous.month] + previous.isLeapYear() : days_in_month[previous.month];
    }
    return previous;
  }

  std::string toString() const {
    char buf[11];
    sprintf(buf, "%d/%d/%d", month, day, year);
    return std::string(buf);
  }

  int usFormat() const {
    return std::stoi(std::to_string(year*10000 + month * 100 + day));
  };

  Date& operator=(const Date& other) {
    day = other.day;
    month = other.month;
    year = other.year;
    return *this;
  };

  bool operator>(const Date& other) const {
    return (this->usFormat() > other.usFormat());
  }

  bool operator<(const Date& other) const {
    return (this->usFormat() < other.usFormat());
  }

  bool operator==(const Date& other) const {
    return (this->usFormat() == other.usFormat());
  }

  bool operator!=(const Date& other) const {
    return !(*this == other);
  }

  bool operator>=(const Date& other) const {
    return (*this > other || *this == other);
  }

  bool operator<=(const Date& other) const {
    return (*this < other || *this == other);
  }
};

class DateRange {
public:
  DateRange(const std::string& _start, const std::string& _end ) 
  : start(Date(_start)), end(Date(_end)) {};

  DateRange(const Date& _start, const Date& _end ) : start(Date(_start)), end(Date(_end)) {};
  
  Date start, end;

  bool includes(const DateRange& other) const {
    return (this->start <= other.start && other.end <= this->end);
  };

  bool overlapsOrContiguous(const DateRange& other) const {
      return !(this->end.usFormat() < other.start.usFormat() - 1 
      || this->start.usFormat() > other.end.usFormat() + 1);
 }

  void merge(const DateRange& other) {
    this->start = (this->start < other.start) ? this->start : other.start;
    this->end = (this->end > other.end) ? this->end : other.end;
  }

  bool operator<(const DateRange& other) const {
    return this->start < other.start || this->start == other.start && this->end < other.end;
  }

  bool operator>(const DateRange& other) const {
    return *this != other && !(*this < other);
  }

  bool operator<=(const DateRange& other) const {
    return (*this < other || *this == other);
  }

  bool operator>=(const DateRange& other) const {
    return (*this > other || *this == other);
  }

  bool operator==(const DateRange& other) const {
    return this->start == other.start && this->end == other.end;
  }

  bool operator!=(const DateRange& other) const {
    return !(*this == other);
  }

  std::string toString() const {
    std::stringstream ss;
    ss << start.toString();
    if (start != end) {
        ss << " to " << end.toString();
    }
    return ss.str();
  }
};

class StockQuoteManager {
public:
  void addPastRange(const std::string& start, const std::string& end) {
    pastRanges.push_back(DateRange(start, end));
  }
  
  void addRequiredRange(const std::string& start, const std::string& end) {
    requiredRanges.push_back(DateRange(start, end));
  }

  bool isValid(const DateRange& d) const {
    return (d.start < d.end);
  }

  std::vector<DateRange> mergeRanges(std::vector<DateRange> neededRanges) {
    if (neededRanges.empty()) {
        return {};
    }

    std::vector<DateRange> mergedNeededRanges;
    DateRange currentRange = neededRanges[0];
    
    for (size_t i = 1; i < neededRanges.size(); ++i) {
      if (currentRange.overlapsOrContiguous(neededRanges[i])) {
          currentRange.merge(neededRanges[i]);
      } else {
          mergedNeededRanges.push_back(currentRange);
          currentRange = neededRanges[i];
      }
    }
    
    mergedNeededRanges.push_back(currentRange);
    return mergedNeededRanges;
  }

  void updateRanges() {
    requiredRanges = mergeRanges(requiredRanges);
    pastRanges = mergeRanges(pastRanges);
  }

  std::vector<DateRange> reverseProcessRanges() {
    std::sort(requiredRanges.begin(), requiredRanges.end());
    std::sort(pastRanges.begin(), pastRanges.end(), std::greater<DateRange>());
    updateRanges();

    std::vector<DateRange> neededRanges;

    for (const auto& req : requiredRanges) {
      bool needed = true;
      for (auto& past : pastRanges) {
        if (isValid(req) && past.overlapsOrContiguous(req)) {
          if (!past.includes(req)) {
            if (req.includes(past)) {
              // Remove the part that is in past
              if (req.start < past.start)  
                neededRanges.push_back(DateRange(req.start, past.start.previousDay())); 
              if (req.end > past.end)
                neededRanges.push_back(DateRange(past.end.nextDay(), req.end));
            } else if (past.start <= req.start && req.end <= past.end) {
              neededRanges.push_back(DateRange(past.end.nextDay(), req.start.previousDay()));
            } else if (past < req) {
              neededRanges.push_back(DateRange(past.end.nextDay(), req.end));
            } else if (req < past) {
              neededRanges.push_back(DateRange(req.start, past.start.previousDay()));
            }
            //past.merge(req);
          }
          needed = false;
          break;
        }
      }

      if (needed && isValid(req)) {
        neededRanges.push_back(req);
      }
    }
    return mergeRanges(neededRanges);
  }

  std::vector<DateRange> processRanges() {
    std::sort(requiredRanges.begin(), requiredRanges.end());
    std::sort(pastRanges.begin(), pastRanges.end());
    updateRanges();

    std::vector<DateRange> neededRanges;
    
    for (const auto& req : requiredRanges) {
      bool needed = true;
      for (auto& past : pastRanges) {
        if (isValid(req) && past.overlapsOrContiguous(req)) {
          if (!past.includes(req)) {
            if (req.includes(past)) {
              // Remove the part that is in past
              if (req.start < past.start)  
                neededRanges.push_back(DateRange(req.start, past.start.previousDay())); 
              if (req.end > past.end)
                neededRanges.push_back(DateRange(past.end.nextDay(), req.end));
            } else if (past.start <= req.start && req.end <= past.end) {
              neededRanges.push_back(DateRange(past.end.nextDay(), req.start.previousDay()));
            } else if (past < req) {
              neededRanges.push_back(DateRange(past.end.nextDay(), req.end));
            } else if (req < past) {
              neededRanges.push_back(DateRange(req.start, past.start.previousDay()));
            }
            //past.merge(req);
          }
          needed = false;
          break;
        }
      }

      if (needed && isValid(req)) {
        neededRanges.push_back(req);
      }
    }
    return mergeRanges(neededRanges);
  }

private:
  std::vector<DateRange> pastRanges;
  std::vector<DateRange> requiredRanges;
};

int main() {
  std::ofstream out;
  out.open("my_output.txt", std::ios::app);
  int NX, NR;
  int caseNumber = 1;
  
  while (std::cin >> NX >> NR) {
    if (NX == 0 && NR == 0) break;
    
    StockQuoteManager manager;
    
    for (int i = 0; i < NX; ++i) {
      std::string start, end;
      std::cin >> start >> end;
      manager.addPastRange(start, end);
    }
    
    for (int i = 0; i < NR; ++i) {
      std::string start, end;
      std::cin >> start >> end;
      manager.addRequiredRange(start, end);
    }

    manager.processRanges();
    std::vector<DateRange> result = manager.reverseProcessRanges();
    
    std::cout << "Case " << caseNumber << ":\n";
    out << "Case " << caseNumber << ":\n";
    if (result.empty()) {
      std::cout << "No additional quotes are required.\n";
      out << "    " << "No additional quotes are required.\n";
    } else {
      for (const auto& r : result) {
        std::cout << r.toString() << "\n";
        out << "    " << r.toString() <<  std::endl;
      }
    }
    caseNumber++;
    if (caseNumber == 35) 
      std::cout << "Will fail" << std::endl;
    out << "\n";
  }
  out.close();
  
  return 0;
}

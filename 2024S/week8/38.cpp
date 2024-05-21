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
    days_in_month[2] = 28 + next.isLeapYear();

    next.day++;
    if (next.day > days_in_month[next.month]) {
      next.day = 1;
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
    days_in_month[2] = 28 + previous.isLeapYear();

    previous.day--;
    if (!previous.day) {
      previous.month--;
      if (!previous.month) {
        previous.year--;
        previous.month = 12;
      }
      previous.day = days_in_month[previous.month];
    }
    return previous;
  }

  std::string toString() const {
    char buf[11];
    sprintf(buf, "%d/%d/%d", month, day, year);
    return std::string(buf);
  }

  std::string usFormat() const {
    return std::to_string(year*10000 + month * 100 + day);
  };

  Date& operator=(const Date& other) {
    day = other.day;
    month = other.month;
    year = other.year;
    return *this;
  };

  bool operator>(const Date& other) const {
    return std::stoi(this->usFormat()) > std::stoi(other.usFormat());
  }

  bool operator<(const Date& other) const {
    return std::stoi(this->usFormat()) < std::stoi(other.usFormat());
  }

  bool operator==(const Date& other) const {
    return std::stoi(this->usFormat()) == std::stoi(other.usFormat());
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
  DateRange(const std::string& _start, const std::string& _end ) : start(Date(_start)), end(Date(_end)) {};
  DateRange(const Date& _start, const Date& _end ) : start(Date(_start)), end(Date(_end)) {};
  Date start, end;

  bool include(const DateRange& other) const {
    return (this->start <= other.start && other.end <= this->end);
  };

  bool overlaps(const DateRange& other) const {
    return (this->include(other) || other.include(*this) 
    || (*this < other && this->end > other.start) || (other < *this && other.end > this->start));
  }

  bool contiguous(const DateRange& other) const {
    return (this->start == other.end || this->end == other.start);
  };

  bool overlapsOrContiguous(const DateRange& other) const {
    return !(this->end < other.start.previousDay() || other.end.nextDay() < this->start);
  }
  // bool overlapsOrContiguous(const DateRange& other) const {
  //     return !(this->end < other.start - 1 || this->start > other.end + 1);
  // }

  void merge(const DateRange& other) {
    this->start = (this->start < other.start) ? this->start : other.start;
    this->end = (this->end > other.end) ? this->end : other.end;
  }

  bool operator<(const DateRange& other) const {
    return this->start < other.start;
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
  
  std::vector<DateRange> processRanges() {
    updateRanges();
    std::sort(requiredRanges.begin(), requiredRanges.end());
    std::sort(pastRanges.begin(), pastRanges.end());
    
    std::vector<DateRange> neededRanges;

    // Find out which requiredRanges had been requested in the pastRanges
    // Three situation can happen:
    // - The requiredRange is all included in a pastRange (1)
    // - The requiredRange is partly included in a pastRanges (2)
    // - The requiredRange is not included at all in the pastRange (3)
    //
    // Case 1: requiredRange not needed, skip it 
    // Case 2: Modify the required range by removing the part that is the pastRange and add it
    // Case 3: Add it as it is to the neededRanges
    
    for (const auto& req : requiredRanges) {
      bool needed = true;
      for (auto& past : pastRanges) {
        if (past.overlapsOrContiguous(req)) {
          if (!past.include(req)) {
            if (req.include(past)) {
              // Remove the part that is in past 
              neededRanges.push_back(DateRange(req.start, past.start.previousDay())); 
              neededRanges.push_back(DateRange(past.end.nextDay(), req.end));
            } else if (past < req) {
              neededRanges.push_back(DateRange(past.end.nextDay(), req.end));
            } else if (req < past) {
              neededRanges.push_back(DateRange(req.start, past.start.previousDay()));
            }
            past.merge(req);
          }
          needed = false;
          break;
        }
      }

      if (needed) {
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
  out.open("output.txt", std::ios::app);
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
    
    std::vector<DateRange> result = manager.processRanges();
    
    std::cout << "Case " << caseNumber << ":\n";
    out << "Case " << caseNumber << ":\n";
    if (result.empty()) {
      std::cout << "No additional quotes are required.\n";
      out << "No additional quotes are required.\n";
    } else {
      for (const auto& r : result) {
        std::cout << r.toString() << "\n";
        out << r.toString() <<  std::endl;
      }
    }
    caseNumber++;
  }
  out.close();
  
  return 0;
}

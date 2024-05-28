// Credits: https://github.com/morris821028/UVa/blob/master/temp/UVaDate/1032%20-%20Intersecting%20Dates.cpp

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#define MAXN 128
#define NEEDED 1
int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Date {
public:
    int value;
    Date() {};
    Date(const int d) : value(d) {};

    bool isLeapYear(int year) const {
        return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
    }

    Date nextDay() const {
      int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

      int year = value / 10000, month = value % 10000/100, day = value % 100;

      if ((year%4 == 0 && year%100 != 0) || year%400 == 0)
        days_in_month[2] = 29;
      day++;

      if (day > days_in_month[month])	day = 1, month++;
      if (month == 13)		month = 1, year++;

      return Date(year * 10000 + month * 100 + day);
    }

    Date previousDay() const {
      int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
      int year = value / 10000, month = value % 10000/100, day = value % 100;

      if ((year%4 == 0 && year%100 != 0) || year%400 == 0)
        days_in_month[2] = 29;
      if (month == 1 && day == 1) 
        year--, month = 12, day = 31;
      else {
        day--;
        if (day < 1)
          month--, day = days_in_month[month];
      }
      return Date(year * 10000 + month * 100 + day);
    }

    friend std::ostream& operator<<(std::ostream& out, const Date& d) {
      // int yy = d.value / 10000, mm = d.value % 10000 / 100, dd = d.value % 100;
      out << d.value % 10000 / 100 << "/" << d.value % 100 << "/" << d.value / 10000;
      return out;
    }
};

class DateRange {
public:
    int start, end;
    DateRange() {}; 
    DateRange(int s, int e) : start(s), end(e) {};
};

class StockQuoteManager {
    std::map<int, int> calendar;
    std::vector<DateRange> pastRequests;
    std::vector<DateRange> newRequests;
    int NX, NR;
public:
    StockQuoteManager() {}; 

    void record(int date) {
        calendar[date] = 0;
        calendar[Date(date).nextDay().value] = 0;
        calendar[Date(date).previousDay().value] = 0;
    };

    void clear() {
        calendar.clear();
        pastRequests.clear();
        newRequests.clear();
    }

    void processRequests() {
        int start, end, i, j, size, cases = 0;
        while (std::cin >> NX >> NR && (NX + NR)) {
            clear();

            for (i = 0; i < NX; ++i) {
                std::cin >> start >> end;
                pastRequests.push_back(DateRange(start, end));
                record(start);
                record(end);
            }

            for (i = 0; i < NR; ++i) {
                std::cin >> start >> end;
                newRequests.push_back(DateRange(start, end));
                record(start);
                record(end);
            }

            size = 0;
            std::vector<Date> date;
            for (auto it = calendar.begin(); it != calendar.end(); it++) {
                it->second = size++;
                date.push_back(Date(it->first));
            }

            // Checkmark the requested dates in the calendar
            std::vector<int> mark(size, 0);
            for (i = 0; i < NR; ++i) {
                start = calendar[newRequests[i].start];
                end = calendar[newRequests[i].end];
                for (j = start; j <= end; ++j) 
                    mark[j] = NEEDED;
            }

            // Iterate over the pastRequests and mark the available quotes
            for (i = 0; i < NX; ++i) {
                start = calendar[pastRequests[i].start];
                end = calendar[pastRequests[i].end];
                for (j = start; j <= end; ++j) 
                    mark[j] = !NEEDED;
            }

            std::cout << "Case " << ++cases << ":\n";
            bool quoteNeeded = false;
            for (i = 0; i < mark.size(); ++i) {
                if (mark[i] == NEEDED) {
                    quoteNeeded = true;
                    std::cout << date[i];

                    // Traversing the ranges
                    if (i + 1 < mark.size() && mark[i + 1] == NEEDED) {
                        std::cout << " to ";
                        while (i + 1 < mark.size() && mark[i + 1] == NEEDED)
                            i++;
                        std::cout << date[i];
                    }
                    std::cout << std::endl;
                }
            }

            if (!quoteNeeded) 
                std::cout << "No additional quotes are required.\n";
        }
    }
};

int main() {
    StockQuoteManager manager;
    manager.processRequests();
    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <sstream>
#include <fstream>

// Date utility functions and class
int days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Date {
public:
    int day, month, year;
    Date() {};
    Date(std::string date) { parseDate(date); };
    Date(const Date& other) : day(other.day), month(other.month), year(other.year) {};

    void parseDate(std::string date) {
        sscanf(date.c_str(), "%4d%2d%2d", &year, &month, &day);
    }

    bool isLeapYear() const {
        return (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));
    }

    Date nextDay() const {
        Date next = *this;
        next.day++;
        if (next.day > days_in_month[next.month] + (next.month == 2 && next.isLeapYear())) {
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
        previous.day--;
        if (previous.day == 0) {
            previous.month--;
            if (previous.month == 0) {
                previous.year--;
                previous.month = 12;
            }
            previous.day = days_in_month[previous.month] + (previous.month == 2 && previous.isLeapYear());
        }
        return previous;
    }

    std::string toString() const {
        char buf[11];
        sprintf(buf, "%d/%d/%d", month, day, year);
        return std::string(buf);
    }

    int usFormat() const {
        return year * 10000 + month * 100 + day;
    }

    Date& operator=(const Date& other) {
        if (this != &other) {
            day = other.day;
            month = other.month;
            year = other.year;
        }
        return *this;
    }

    bool operator>(const Date& other) const {
        return this->usFormat() > other.usFormat();
    }

    bool operator<(const Date& other) const {
        return this->usFormat() < other.usFormat();
    }

    bool operator==(const Date& other) const {
        return this->usFormat() == other.usFormat();
    }

    bool operator!=(const Date& other) const {
        return !(*this == other);
    }

    bool operator>=(const Date& other) const {
        return !(*this < other);
    }

    bool operator<=(const Date& other) const {
        return !(*this > other);
    }
};

// DateRange class to represent date ranges and their operations
class DateRange {
public:
    Date start, end;

    DateRange(const std::string& _start, const std::string& _end)
        : start(Date(_start)), end(Date(_end)) {}

    DateRange(const Date& _start, const Date& _end)
        : start(_start), end(_end) {}

    bool includes(const DateRange& other) const {
        return (start <= other.start && other.end <= end);
    }

    bool overlapsOrContiguous(const DateRange& other) const {
        return !(end.usFormat() < other.start.usFormat() - 1 || start.usFormat() > other.end.usFormat() + 1);
    }

    void merge(const DateRange& other) {
        start = std::min(start, other.start);
        end = std::max(end, other.end);
    }

    bool operator<(const DateRange& other) const {
        return start < other.start || (start == other.start && end < other.end);
    }

    bool operator>(const DateRange& other) const {
        return other < *this;
    }

    bool operator<=(const DateRange& other) const {
        return !(other < *this);
    }

    bool operator>=(const DateRange& other) const {
        return !(*this < other);
    }

    bool operator==(const DateRange& other) const {
        return start == other.start && end == other.end;
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

// StockQuoteManager class to manage the stock quote periods
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
                out << "    " << r.toString() << std::endl;
            }
        }
        caseNumber++;
        out << "\n";
    }
    out.close();

    return 0;
}

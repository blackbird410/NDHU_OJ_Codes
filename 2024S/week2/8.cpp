#include <iostream>
#include <math.h>
using namespace std;

class Point {
public:
  Point(double _x, double _y) {
    x = _x;
    y = _y;
  }

  double getX() {
    return x;
  }

  double getY() {
    return y;
  }
private:
  double x, y;
};

class Segment {
public:
  Segment(Point _start, Point _end) {
    start = new Point(_start.getX(), _start.getY());
    end = new Point(_end.getX(), _end.getY());
  }

  double length() {
    return sqrt(pow(end->getX() - start->getX(), 2) + pow(end->getY() - start->getY(), 2));
  }

  Point getEnd(int value) {
    Point p(start->getX(), start->getY());
    Point q(end->getX(), end->getY());
    return (value) ? q : p;
  }

  void display() {
    cout << "(" << start->getX() << ", " << start->getY() << ")" << " -> " << "(" << end->getX() << ", " << end->getY() << ")" << endl; 
  }
private:
  Point *start, *end;
};

class Path {
public:
  Path(Segment* segments, int length) {
    int i = 0;
    double lengthSum = 0;
    for (i = 0; i < length - 1; i++) {
      if (!isSame(segments[i].getEnd(1), segments[i + 1].getEnd(0))) {
        break;
      }
      lengthSum += segments[i].length();
    }

    if (i == length - 1) {
      lengthSum += segments[i].length();
      double v = (isSame(segments[i].getEnd(1), segments[0].getEnd(0))) ? -1 : lengthSum;
      cout << v << endl;
    } else { 
      cout << -1 << endl; 
    }
  }

  bool isSame(Point a, Point b) {
    return (a.getX() == b.getX() && a.getY() == b.getY());
  }
};

int main() {
  double a[] = {1, 2, 3, 4, 5, 6, 7, 8};
  Point p(a[0], a[1]);
  Point q(a[2], a[3]);
  Point r(a[4], a[5]);
  Point s(a[6], a[7]);

  Segment s1(p, q);
  Segment s2(q, r);
  Segment s3(r, s);

  Segment array[] = {s1, s2, s3};
  Path path(array, sizeof(array) / sizeof(s));
  
  return 0;
}

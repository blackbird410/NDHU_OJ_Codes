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

  Point getStart() {
    Point p(start->getX(), start->getY());
    return p;
  }

  Point getEnd() {
    Point p(end->getX(), end->getY());
    return p;
  }
  double length() {
    return sqrt(pow(end->getX() - start->getX(), 2) + pow(end->getY() - start->getY(), 2));
  }

  Point getEnd(int value) {
    Point p(start->getX(), start->getY());
    Point q(end->getX(), end->getY());
    return (value) ? p : q;
  }

  void display() {
    cout << "(" << start->getX() << ", " << start->getY() << ")" << " -> " << "(" << end->getX() << ", " << end->getY() << ")" << endl; 
  }
private:
  Point *start, *end;
};

int main() {
  double a[4] = {1, 2, 3, 4};
  Point p(a[0], a[1]);
  Point q(a[2], a[3]);
  Segment s(p, q);

  s.display();
  cout << s.getEnd(0).getX() << " / " << s.getEnd(1).getX() << endl;
  
  return 0;
}

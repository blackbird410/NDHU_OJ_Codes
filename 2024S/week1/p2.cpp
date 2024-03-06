#include <iostream>
#include <cmath>
using namespace std;

class Point {
public:
  void setX(double newX) {
    x = newX;
  }
  
  void setY(double newY) {
    y = newY;
  }

  double getX() {
    return x; 
  }

  double getY() {
    return y;
  }

private:
  double x;
  double y;
};

class Segment {
public: 
  Point start;
  Point end;

  double distance() {
    return sqrt(pow(start.getX() - end.getX(), 2) + pow(start.getY() - end.getY(), 2));
  }

  void display() {
    cout << start.getX() << endl;
    cout << start.getY() << endl;
    cout << end.getX() << endl;
    cout << end.getY() << endl;
  }
};

void takeInput(Segment* s) {
  double startX;
  double startY;
  double endX;
  double endY;

  cin >> startX;
  cin >> startY;
  cin >> endX;
  cin >> endY;

  s->start.setX(startX);
  s->start.setY(startY);
  s->end.setX(endX);
  s->end.setY(endY);
}

int main() {
  int n, i;
  Segment s;

  cin >> n;
  for (i = 0; i < n; i++) {
    takeInput(&s);
    cout << s.distance() << endl;
  }

  return 0;
}

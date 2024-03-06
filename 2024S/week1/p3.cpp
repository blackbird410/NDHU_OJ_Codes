#include <iostream>
#include <cmath>
using namespace std;

#define N_SIDES 3
#define N_POINTS 3

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
};

class Triangle {
public:
  Point pts[N_POINTS];

  void setPts(Point* newPts) {
    int i;

    for (i = 0; i < N_POINTS; i++) {
      pts[i].setX(newPts[i].getX());
      pts[i].setY(newPts[i].getY());
    }
  }

  void display() {
    int i;
    for (i = 0; i < N_POINTS; i++)
      cout << "(" << pts[i].getX() << ", " << pts[i].getY() << ")" << endl;
  }

  double perimeter() {
    Segment s;
    int i;
    double p = 0;

    for (i = 0; i < N_SIDES - 1; i++) {
      s.start.setX(pts[i].getX());
      s.start.setY(pts[i].getY());
      s.end.setX(pts[i + 1].getX());
      s.end.setY(pts[i + 1].getY());
      p += s.distance();
    }

    // Setting the last segment
    s.start.setX(pts[i].getX());
    s.start.setY(pts[i].getY());
    s.end.setX(pts[0].getX());
    s.end.setY(pts[0].getY());
    p += s.distance();

    return p;
  }
};

void takeInput(Triangle* t) {
  int i;
  double temp;
  Point pts[N_POINTS];

  for(i = 0; i < N_POINTS; i++) {
    cin >> temp;
    pts[i].setX(temp);
    cin >> temp;
    pts[i].setY(temp);
  } 

  t->setPts(pts);
}

int main() {
  int n, i;
  Triangle t;

  cin >> n;

  for (i = 0; i < n; i++) {
    takeInput(&t);
    cout << t.perimeter() << endl;
  }

  return 0;
}

#include <iostream>
#include <string>
using namespace std; 

#define MAX_SIZE 1000

class Point {
public:
  double x;
  double y;
  void display() {
    cout << "(" << x << ", " << y << ")"<< endl;
  }
};

void takePoints(Point *points, int n) {
  int i;
  for (i = 0; i < n; i++) {
    cin >> points[i].x;
    cin >> points[i].y;
  }
}

void displayPoints (Point *points, int n) {
  int i;
  for (i = 0; i < n; i++) 
    points[i].display();
}

int main () {
  int i, n = 0;
  Point points[MAX_SIZE];

  cin >> n;
  takePoints(points, n);
  displayPoints(points, n);
  
  return 0;
}

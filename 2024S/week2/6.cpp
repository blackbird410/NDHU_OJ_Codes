#include <iostream>
using namespace std;

class Point {
public:
  Point(float xCoord, float yCoord) {
    x = xCoord;
    y = yCoord;
  }
  float getX() {
    return x;
  }

  float getY() {
    return y;
  }

  void display() {
    cout << "(" << this->getX() << ", " << this->getY() << ")" << endl;
  }
private:
  float x;
  float y;
};

int main() {
  int n = 0;
  float x = 0, y = 0;
  cin >> n;
  n += 1;

  while(--n && n > 0) {
    cin >> x;
    cin >> y;
    Point p(x, y);
    p.display();
  }
  return 0;
}

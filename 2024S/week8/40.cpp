#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define MAX_N_COORD 100

class Coord {
  int x, y;
public:
  Coord() : x(0), y(0) {};
  Coord(int _x, int _y) : x(_x), y(_y) {};
  Coord(const Coord& c) : x(c.x), y(c.y) {};
  void setX(int newX) { x = newX; };
  int getX() { return x; }
  void setY(int newY) { y = newY; };
  int getY() { return y; }

  bool operator<(const Coord& other) const {
    return (x < other.x || (x==other.x && y < other.y));
  }

  bool operator>(const Coord& other) const {
    return (x > other.x || (x==other.x && y > other.y));
  }
  
  Coord& operator=(const Coord& other) {
    x = other.x;
    y = other.y;
    return *this;
  }

  friend double getDistance(Coord& start, Coord& end) {
    return sqrt(pow(end.getX() - start.getX(), 2) + pow(end.getY() - start.getY(), 2));
  };

  friend std::ostream &operator<<( std::ostream& out, const Coord& c) {
    out << "(" << c.x << ", " << c.y << ")";
    return out;
  }
};


std::vector<Coord> getCoords(int n, int* y_max) {
  std::vector<Coord> coords;
  int x, y;

  coords.push_back(Coord(0, 0));
  while (--n >= 0) {
    std::cin >> x >> y;
    *y_max = (y > *y_max)  ? y : *y_max;
    coords.push_back(Coord(x, y));
  }
  std::sort(coords.begin(), coords.end(), std::greater<Coord>());
  
  return coords;
};

double getDistance(std::vector<Coord>& coords, int* y_max) {
  int i, temp_y_max = 0;
  double sum = 0;
  Coord a, b, c, m;

  for (i = 1; i < coords.size() && temp_y_max != *y_max; ++i) {
    if( coords[i].getY() > temp_y_max) {

      b = coords[i];
      c = coords[i-1];
      a = Coord(b.getX(), c.getY());

      sum += getDistance(b, c) - sqrt(pow(temp_y_max - c.getY(), 2) * (1 + pow(getDistance(a, c), 2) / pow(getDistance(a, b) ,2))); 

      temp_y_max = coords[i].getY();
    }
  }
  
  return sum;
}

int main() {
  int test_cases = 0, nCoords = 0, y_max = 0;
  size_t i;
  double d;

  std::cin >> test_cases;
  test_cases++;

  while (--test_cases) {
    std::cin >> nCoords;

    std::vector<Coord> coords = getCoords(nCoords, &y_max);
    d = getDistance(coords, &y_max);
    printf("%.2lf\n", d);
  }

  return 0;
}

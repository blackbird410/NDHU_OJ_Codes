#include <iostream>
#include <cmath>
using namespace std;

class Segment {
public: 
  double start;
  double end;

  void setSegment(double a, double b) {
    if (a > b) {
      start = b;
      end = a;
    } else {
      start = a;
      end = b;
    }
  }

  double getStart() {
    return start;
  }

  double getEnd() {
    return end;
  }
};

int main() {
  int a, b, c, d;
  Segment ab, cd;

  cin >> a;
  cin >> b;
  cin >> c;
  cin >> d;

  ab.setSegment(a, b);
  cd.setSegment(c, d);

  if (ab.getStart() < cd.getStart()) {
    if (ab.getEnd() > cd.getStart())
      cout << "overlay" << endl;
    else 
      cout << "no overlay" << endl;
  } else {
    if (cd.getEnd() > ab.getStart())
      cout << "overlay" << endl;
    else 
      cout << "no overlay" << endl;
  }
  
}

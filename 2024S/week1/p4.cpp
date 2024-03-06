#include <iostream>
using namespace std;

class Person {
public:
  void setDistance(double d) {
    distance = d;
  }

  void setTime(double t) {
    time = t;
  }

  double getDistance() {
    return distance;
  }

  double getTime() {
    return time;
  }

  double speed() {
    return distance / time;
  }

private:
  double distance;
  double time;
};

int main() {
  Person man;
  double d, t;

  cin >> d;
  cin >> t;

  man.setDistance(d);
  man.setTime(t);
  cout << man.speed() << endl;

  return 0;
}

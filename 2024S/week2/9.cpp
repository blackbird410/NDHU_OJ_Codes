#include <iostream>
#include <math.h>
using namespace std;

class Tollway {
public: 
  Tollway(float tollCharge) {
    charge = tollCharge;
  }
  int getToll(int distance) {
    return (distance > 200) ? round((200 + (distance - 200) * 0.75) * charge) : round(distance * charge); 
  }
private:
  float charge;
};

int main() {
  int distance = 0;
  cin >> distance;
  Tollway t(1.2);
  cout << t.getToll(distance) << endl;
  return 0;
}


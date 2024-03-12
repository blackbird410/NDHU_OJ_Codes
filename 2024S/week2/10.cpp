#include <iostream>
#include <string>
using namespace std;

class Plate {
public:
  Plate(int number) {
    n = number;
  }

  string isThereFour() {
    int temp = this->n;
    while(temp) {
      if (temp % 10 == 4) 
        return "Yes";
      temp /= 10;
    }
    return "No";
  }
private:
  int n;
};

int main() {
  int plate = 0;
  cin >> plate;
  if (plate > 0) {
    Plate p(plate);
    cout << p.isThereFour() << endl;
  }

  return 0;
}

#include <cmath>
#include <iostream>

class PrimeEmirpOrNone {
	int value;
public:
	PrimeEmirpOrNone(int n) : value(n) {
		if (!isPrime(value)) std::cout << value << " is not prime." << std::endl;
		else if (!isEmirp()) std::cout << value << " is prime." << std::endl;
		else std::cout << value << " is emirp." << std::endl;
	};
	void setValue(int v) { value = v; }; 

	bool isPrime(int v) const {
		if (v <= 1) return false;
		for(int i = 2; i < std::sqrt(v); ++i) 
			if (v % i == 0) return false;
		return true;
	}

	int reverse () {
		int r = 0;
		int temp = value;
		while(temp) {
			r = r * 10 + temp % 10;
			temp /= 10;
		}
		return r;
	}

	bool isEmirp() {
		if(!isPrime(value)) return false;
		int r = reverse();
		return r != value && isPrime(r);
	}
};

int main() {
	int testCase;
	while (std::cin >> testCase) {
		PrimeEmirpOrNone test(testCase);
	}

	return 0;
}

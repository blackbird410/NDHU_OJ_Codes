#include <iostream>
#include <cstdio>
#include <ostream>

class MaxCycle {
	unsigned int first, second;
public:
	MaxCycle() : first(0), second(0) {};
	MaxCycle(unsigned int a, unsigned int b) : first( a < b ? a : b), second(b > a ? b : a) {};

	void setFirst(unsigned int a) { first =  a; };
	void setSecond(unsigned int b) { second = b; };

	unsigned int getMaxCycle(){
		int current_max = 0, cycle = 0;
		for (int i = first; i <= second; ++i) {
			cycle = maxCycle(i);
			current_max = (cycle > current_max) ? cycle : current_max; 
		}
		return current_max;
	};

	unsigned int maxCycle(unsigned int n)
	{
		if (n == 1)
		{
			return 1;
		}
		else if (n % 2)
		{
			return maxCycle((3*n) + 1) + 1;
		}
		else 
		{
			return maxCycle(n / 2) + 1;
		}
	}
	friend std::ostream& operator<<(std::ostream& out, MaxCycle m) { 
		out << " " << m.getMaxCycle();
		return out;
	}
};

int main()
{
	MaxCycle m;
	int i, j;
	while(std::cin >> i >> j) {
		m = MaxCycle(i, j);
		std::cout << i << " " << j;
		std::cout << m << std::endl;
	}

	return 0;
}

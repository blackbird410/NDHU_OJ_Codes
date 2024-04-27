#include <iostream>
#include "DoubleSubscriptedArray.cpp"

int main() 
{
  DoubleSubscriptedArray a;
  DoubleSubscriptedArray b(2, 2);

  std::cout << "DoubleSubscriptedArray a:\n" << a << std::endl;
  std::cout << "DoubleSubscriptedArray b:\n" << b << std::endl;
  
  std::cout << "Enter " << b.getSize() << " number: ";
  std::cin >> b;
  std::cout << "DoubleSubscriptedArray b:\n" << b << std::endl;

  std::cout << "a == b ? " << ((a == b) ? "Yes" : "No") << std::endl;

  std::cout << "\nAssigning b to a:" << std::endl;
  a = b;
  std::cout << "DoubleSubscriptedArray a:\n" << a << std::endl;

  std::cout << "a == b ? " << ((a == b) ? "Yes" : "No") << std::endl;

  std::cout << "a[0] = " << a[0] << std::endl;
  std::cout << "a[0][1] = " << a[0][1] << std::endl;
  std::cout << "a[0][0] + a[0][1] = " << (a[0][0] + a[0][1]) << std::endl;

  return 0;
}

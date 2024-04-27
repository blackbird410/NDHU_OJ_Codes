#include <iostream>
#include "DoubleSubscriptedArray.cpp"

int main() 
{
  DoubleSubscriptedArray a;
  DoubleSubscriptedArray b(2, 2);

  std::cout << "Array a:\n" << a << std::endl;
  std::cout << "Array b:\n" << b << std::endl;
  
  std::cout << "Enter " << b.getSize() << " number: ";
  std::cin >> b;
  std::cout << "Array b:\n" << b << std::endl;

  std::cout << "Assigning b to a:" << std::endl;
  a = b;
  std::cout << "Array a:\n" << a << std::endl;

  return 0;
}

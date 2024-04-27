#include <iostream> 
#include "Array.cpp"

int main() 
{
  Array a;
  Array b(5);

  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << (a == b) << std::endl;

  std::cout << "Enter " << b.getSize() << " numbers :\n";
  std::cin >> b;
  std::cout << "Assigning b to a:\n";
  a = b;
  std::cout << "Array a:\n" << a << "\nArray b:\n" << b << std::endl;
  
  std::cout << "Initializing array c from a:" << std::endl;
  Array c(a);
  std::cout << "Array c:\n" << c << std::endl;

  std::cout << "c[4] = " << c[4] << std::endl;

  return 0;
}

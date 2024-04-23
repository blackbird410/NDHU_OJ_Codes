#include <iostream>
#include "24.h"

int main ()
{
  int nTop = 0, nPers = 0;

  std::cin >> nTop;
  Topic *topics = new Topic[nTop];
  std::cin >> *topics;

  std::cin >> nPers;
  Personel *personel = new Personel[nPers];
  std::cin >> *personel;

  std::cout << *topics << std::endl;
  std::cout << *personel << std::endl;

  delete[] topics;
  delete[] personel;
  

  return 0;
}

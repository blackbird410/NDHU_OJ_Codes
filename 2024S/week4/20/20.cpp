#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "Grid.h"

int main() 
{
  int testCases = 0;
  std::cin >> testCases;
  testCases++;

  while(--testCases) 
  {
    int m, n, xi, yi;
    std::string command;
    std::cin >> m >> n >> xi >> yi;
    Grid maze(m, n);
    maze.setPosition(xi, yi);
    while (!(maze.getStack().isEmpty())) 
    {
      std::cin >> command;
      maze.processCommand(command);
      std::cout << maze << std::endl;
    }

  }

  return 0;
}

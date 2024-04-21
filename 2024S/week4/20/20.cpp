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
    while(!(getchar()));
    while (!(maze.getStack().isEmpty())) 
    {
      if (!(maze.hasUnvisitedNeighbor(maze.getStack().getTop().getData())))
         maze.getStack().pop();
      else 
      {
        Cell newPosition = maze.getStack().getTop().getData();
        maze.setPosition(newPosition.getP(), newPosition.getQ());
        
        std::getline(std::cin, command);
        maze.processCommand(command);
        //std::cout << maze << std::endl;
      }
    }

    std::cout << maze << std::endl;

  }

  return 0;
}

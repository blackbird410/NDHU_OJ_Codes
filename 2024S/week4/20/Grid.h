#ifndef GRID_h
#define GRID_h

#include <iostream>
#include <string>
#include "Cell.h"
#include "Stack.h"

#define MAXSIZE 40
#define PATH " "
#define V_WALL "|"
#define H_WALL "_"
#define CONNECTED true

typedef struct Coord {
  int x, y;
  friend std::ostream &operator<<( std::ostream &out, const Coord& c)
  {
    out << "(" << c.x << ", " << c.y << ")";
    return out;
  }
} Coord;

class Grid 
{
private:
  int row, col;
  Coord position;
  Stack visited;
  Cell *board;
public:
  explicit Grid(int m, int n) 
    : row((m > 0 && m < MAXSIZE) 
          ? m : throw std::out_of_range("Row out of range.")), 
    col((n > 0 && n < MAXSIZE) 
        ? n : throw std::out_of_range("Row out of range.")), 
    board( new Cell[ row * col ])
  {
    size_t i = 0, j = 0;
    for ( i = 0; i < row; ++i ) 
      for ( j = 0; j < col; ++j )
        board[i * col + j] = Cell(row - i, j + 1);
  };

  ~Grid() 
  {
    delete[] board;
  }

  void setPosition( int x, int y )
  {
    position.x  = (x >= 0 && x < col ) 
    ? x : throw std::invalid_argument("Invalid x coordinate for cell position.");
    position.y = (y >= 0 && y < row) 
      ? y : throw std::invalid_argument("Invalid y coordinate for cell position.");
    updateVisited();
  };

  bool hasUnvisitedNeighbor(Cell &c) 
  {
    Coord p = c.getPosition();

    // Checking UP, DOWN, LEFT and RIGHT in the specified order
    return (p.y < row && !(board[ (row - p.y - 1) * col + p.x ].getVisitedStatus())) 
      || (p.y > 1  && !(board[ (row - p.y + 1) * col + p.x ].getVisitedStatus())) 
      || ( p.x > 1 && !(board[ (row - p.y) * col + (p.x - 1) ].getVisitedStatus())) 
      || ( p.x < col && !(board[ ( row - p.y) * col + (p.x + 1)].getVisitedStatus())));
  }

  void updateVisited()
  {
    // Push the current position to the visited Stack
    Cell temp(position.x, position.y);
    temp.setVisitedStatus(true);
    Node n(temp);
    visited.push(n);

    // Check if the last cell added to the least has at least one unvisited neighbor 
    while (!(visited.getTop().hasUnvisitedNeighbor()))
      pop();

    std::cout << "Visited: " << visited << std::endl;
  }

  Coord &getPosition(){ return position; }; 

  int getRow() { return row; };
  int getCol() { return col; };
  Stack &getStack() { return visited; };

  void move(int direction) 
  {
    // If a cell has been visited, can we allow it to be visited twice

    switch (direction) 
    {
      case UP:
        if (position.y < row)
        {
          // Creates a path between the two cells
          board[(row - position.y) * col + (position.x - 1)].setNeighbor(UP, CONNECTED);
          position.y += 1;
          board[(row - position.y) * col + (position.x - 1)].setNeighbor(DOWN, CONNECTED);
        }
        break;
      case DOWN:
        if (position.y > 1)
        {
          board[(row - position.y) * col + (position.x - 1)].setNeighbor(DOWN, CONNECTED);
          position.y -= 1;
          board[(row - position.y) * col + (position.x - 1)].setNeighbor(UP, CONNECTED);
        }
        break;
      case LEFT:
        if (position.x > 1)
        {
          board[(row - position.y) * col + (position.x - 1)].setNeighbor(LEFT, CONNECTED);
          position.x -= 1;
          board[(row - position.y) * col + (position.x - 1)].setNeighbor(RIGHT, CONNECTED);
        }
        break;
      case RIGHT:
        if (position.x < col)
        {
          board[(row - position.y) * col + (position.x - 1)].setNeighbor(RIGHT, CONNECTED);
          position.x += 1;
          board[(row - position.y) * col + (position.x - 1)].setNeighbor(LEFT, CONNECTED);
        }
        break;
      default:
        break;
    }
    // Add the new cell visited to the Stack
    updateVisited();
  }

  void processCommand(std::string c) 
  {
    if (c.at(0) == 'F')
    {
      int flipIndex = 0;
      size_t i = 1;
      while (++i < c.length()) 
      {
        flipIndex += ( c[i] >= '0' && c[i] <= '9' ) 
          ? c[i] - '0' 
          : throw std::invalid_argument("Invalid command.");
      }

      // Flip the stack of the visited cells
      visited.flip(flipIndex);
    }
    else 
    {
       switch(c[0]) 
      {
        case 'U':
          move(UP);
          break;
        case 'L':
          move(LEFT);
          break;
        case 'D':
          move(DOWN);
          break;
        case 'R':
          move(RIGHT);
          break;
        default:
          break;
      }
    }
  }

  friend std::ostream &operator<<( std::ostream &out, const Grid& g)
  {
    size_t i = 0, j = 0;

    // First display the top border
    for ( j = 0; j < g.col; ++j )
      out << " " << H_WALL;
    out << std::endl;

    for ( i = 0; i < g.row; ++i )
    {
      for ( j = 0; j < g.col; ++j )
      {
        if ( j == 0 ) out << V_WALL;
        out << (( g.board[ i * g.col + j ].getNeighbor(DOWN) ) ? PATH : H_WALL);
        out << (( g.board[ i * g.col + j ].getNeighbor(RIGHT) ) ? PATH : V_WALL);
      }
      out << std::endl;
    }

    return out;
  }

};

#endif

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
  int p, q;
  Coord () {};
  Coord(int _p, int _q) : p(_p), q(_q) {};
  friend std::ostream &operator<<( std::ostream &out, const Coord& c)
  {
    out << "(" << c.p << ", " << c.q << ")";
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

  void setPosition( int p, int q )
  {
    position.p  = (p >= 0 && p <= row ) 
    ? p : throw std::invalid_argument("Invalid p coordinate for cell position.");
    position.q = (q >= 0 && q <= col) 
      ? q : throw std::invalid_argument("Invalid q coordinate for cell position.");
    updateVisited();
  };

  bool hasUnvisitedNeighbor(Cell &c) 
  {
    Coord pos(c.getP(), c.getQ());
    int index =  0;
    bool visited = false;

    if (pos.p < row) 
    {
      index = getArrayIndex(pos.p + 1, pos.q);
      visited = board[index].getVisitedStatus();
      if (!visited) return true; 
    }
    
    if (pos.p > 1) 
    {
      index = getArrayIndex(pos.p - 1, pos.q);
      visited = board[index].getVisitedStatus();
      if (!visited) return true; 
    }

    if (pos.q > 1) 
    {
      index = getArrayIndex(pos.p, pos.q - 1);
      visited = board[index].getVisitedStatus();
      if (!visited) return true; 
    }
    
    if (pos.q < col) 
    {
      index = getArrayIndex(pos.p, pos.q + 1);
      visited = board[index].getVisitedStatus();
      if (!visited) return true; 
    }

    // Checking UP, DOWN, LEFT and RIGHT in the specified order
    // return ((p.y < row && !(board[  ].getVisitedStatus())) 
    //   || (p.y > 1  && !(board[  ].getVisitedStatus())) 
    //   || ( p.x > 1 && !(board[ (row - p.y) * col + p.x - 2 ].getVisitedStatus())) 
    //   || ( p.x < col && !(board[ ( row - p.y) * col + p.x ].getVisitedStatus())));
    return false;
  }

  int getArrayIndex(Coord &p) { return ( row - p.p) * col + p.q - 1; };
  int getArrayIndex(int p, int q) { return ( row - p) * col + q - 1; };

  void updateVisited()
  {
    // Push the current position to the visited Stack
    int index = getArrayIndex(position);
    if (!(board[index].getVisitedStatus())) {
      board[index].setVisitedStatus(true);
      Node n(board[index]);
      visited.push(n);
    }
  }

  Coord &getPosition(){ return position; }; 

  int getRow() { return row; };
  int getCol() { return col; };
  Stack &getStack() { return visited; };

  void move(int direction) 
  {
    switch (direction) 
    {
      case UP:
        if (position.p < row)
        {
          // Creates a path between the two cells
          board[getArrayIndex(position)].setNeighbor(UP, CONNECTED);
          position.p += 1;
          board[getArrayIndex(position)].setNeighbor(DOWN, CONNECTED);
        }
        break;
      case DOWN:
        if (position.p > 1)
        {
          board[getArrayIndex(position)].setNeighbor(DOWN, CONNECTED);
          position.p -= 1;
          board[getArrayIndex(position)].setNeighbor(UP, CONNECTED);
        }
        break;
      case LEFT:
        if (position.q > 1)
        {
          board[getArrayIndex(position)].setNeighbor(LEFT, CONNECTED);
          position.q -= 1;
          board[getArrayIndex(position)].setNeighbor(RIGHT, CONNECTED);
        }
        break;
      case RIGHT:
        if (position.q < col)
        {
          board[getArrayIndex(position)].setNeighbor(RIGHT, CONNECTED);
          position.q += 1;
          board[getArrayIndex(position)].setNeighbor(LEFT, CONNECTED);
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
      // std::cout << "Stack flipped =>" << visited << std::endl;
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
  };

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

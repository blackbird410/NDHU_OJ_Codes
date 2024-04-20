#ifndef CELL_h
#define CELL_h

#include <iostream>
#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

class Cell
{
  int x, y;
  bool neighbor[4];
  bool isVisited;
public:
  Cell() : isVisited(false) {};
  Cell(Cell &c) 
  {
    setX(c.getX());
    setY(c.getY());
    for( size_t i = 0; i < 4; ++i)
      neighbor[i] = c.getNeighbor(i);
    isVisited = c.getVisitedStatus();
  }

  Cell(int _x, int _y) : isVisited(false) 
  {
    setX(_x);
    setY(_y);
    for( size_t i = 0; i < 4; ++i)
      neighbor[i] = false;
  }

  void setX(int _x) 
  { 
    x = ( _x > 0 ) ? _x : throw std::invalid_argument("Invalid argument");
  };

  void setY(int _y) 
  { 
    y = ( _y > 0 ) ? _y : throw std::invalid_argument("Invalid argument"); 
  };

  void setVisitedStatus(bool status) { isVisited = status; };

  int getX() { return x; };
  int getY() { return y; };
  bool getVisitedStatus() { return isVisited; };
  bool getNeighbor(int index)
  {
    // Returns whether or not a neighbor has been visited
    return ((index >= 0 && index < 4) 
            ? neighbor[index] 
            : throw std::invalid_argument("Invalid argument")); 
  }

  void setNeighbor(int index, bool status)
  {
    neighbor[index] = (index >= 0 && index < 4) 
      ? status 
      : throw std::invalid_argument("Invalid argument");;
  }

  Cell &operator=( const Cell& c )
  {
    // Avoids self-assignment
    if ( this != &c )
    {
      setX(c.x);
      setY(c.y);
      for ( size_t i = 0; i < 4; ++i )
        neighbor[i] = c.neighbor[i];
    }
    return *this;
  }

  bool operator==( const Cell& other )
  {
    if (x != other.x || y != other.y )
      return false;
    for ( size_t i = 0; i < 4; ++i )
      if ( neighbor[i] != other.neighbor[i] )
        return false;

    return true;
  }

  bool operator!=( const Cell& other )
  {
    return !( *this == other );
  }
  
  friend std::ostream &operator<<( std::ostream &out, const Cell& c)
  {
    out << "(" << c.x << ", " << c.y << ")";
    return out;
  }
};

#endif // !CELL_h

#ifndef CELL_h
#define CELL_h

#include <iostream>
#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3

class Cell
{
  int p, q;
  bool neighbor[4];
  bool isVisited;
public:
  Cell() : isVisited(false) {};
  Cell(Cell &c) 
  {
    setP(c.getP());
    setQ(c.getQ());
    for( size_t i = 0; i < 4; ++i)
      neighbor[i] = c.getNeighbor(i);
    isVisited = c.getVisitedStatus();
  }

  Cell(int _p, int _q) : isVisited(false) 
  {
    setP(_p);
    setQ(_q);
    for( size_t i = 0; i < 4; ++i)
      neighbor[i] = false;
  }

  void setP(int _p) 
  { 
    p = ( _p > 0 ) ? _p : throw std::invalid_argument("Invalid argument");
  };

  void setQ(int _q) 
  { 
    q = ( _q > 0 ) ? _q : throw std::invalid_argument("Invalid argument"); 
  };

  void setVisitedStatus(bool status) { isVisited = status; };

  int getP() { return p; };
  int getQ() { return q; };
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
      setP(c.p);
      setQ(c.q);
      for ( size_t i = 0; i < 4; ++i )
        neighbor[i] = c.neighbor[i];
      isVisited = c.isVisited;
    }
    return *this;
  }

  bool operator==( const Cell& other )
  {
    if (p != other.p || q != other.q )
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
    out << "(" << c.p << ", " << c.q << ")";
    return out;
  }
};

#endif // !CELL_h

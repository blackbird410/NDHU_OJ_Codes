#ifndef DOUBLESUBSCRIPTEDARRAY_h
#define DOUBLESUBSCRIPTEDARRAY_h

#include <iostream>
#include "Array.cpp"

class DoubleSubscriptedArray 
{
private:
  int row;
  int col;
  Array **ptr;
public:
  DoubleSubscriptedArray(int = 10, int = 10);
  DoubleSubscriptedArray( const DoubleSubscriptedArray& );
  virtual ~DoubleSubscriptedArray();
  Array* operator[]( const int subscript );
  Array* operator[]( const int subscript ) const;
  bool operator==( const DoubleSubscriptedArray& ) const;
  bool operator!=( const DoubleSubscriptedArray& other ) const 
  {
    return !( *this == other );
  };
  DoubleSubscriptedArray& operator=( const DoubleSubscriptedArray& );

  int getSize() { return row * col; };
  std::pair<int, int> getDimensions() { return std::make_pair( row, col ); };

  friend std::ostream &operator<<( std::ostream &out, const DoubleSubscriptedArray& );
  friend std::istream &operator>>( std::istream &input, DoubleSubscriptedArray& );

};

#endif

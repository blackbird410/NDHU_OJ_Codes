#ifndef ARRAY_h
#define ARRAY_h

#include <iostream>
#include <iomanip>

class Array 
{
private:
  int size;
  int *ptr;
public:
  explicit Array(int = 10);
  Array(const Array &);
  virtual ~Array();
  int &operator[]( const int );
  int operator[]( const int ) const;
  bool operator==( const Array& other ) const;
  bool operator!=( const Array& other ) const 
  {
    return !( *this == other );
  };
  Array &operator=( const Array& );

  int getSize() { return size; };

  friend std::ostream &operator<<( std::ostream &out, const Array& );
  friend std::istream &operator>>( std::istream &input, Array& );
};


#endif // !ARRAY_h


#include <iostream>
#include "DoubleSubscriptedArray.h"

DoubleSubscriptedArray::DoubleSubscriptedArray( int _row, int _col ) 
  : row( _row > 0 ? _row : throw std::invalid_argument("Invalid array row size.")), 
    col( _col > 0 ? _col : throw std::invalid_argument("Invalid array col size.")), 
    ptr( new Array*[row])
{
  size_t i, j;
  for ( i = 0; i < row; ++i )
    ptr[i] = new Array(col);
};

DoubleSubscriptedArray::DoubleSubscriptedArray( const DoubleSubscriptedArray& other ) 
  : row( other.row),
    col( other.col),
    ptr( new Array*[row] )
{
  size_t i, j;
  for ( i = 0; i < row; ++i )
    ptr[i] = new Array(col);

  for ( i = 0; i < row; ++i )
    ptr[i] = other.ptr[i];
};

DoubleSubscriptedArray::~DoubleSubscriptedArray() 
{
  // Free all pointers in Array objects in the DoubleSubscriptedArray
  for ( size_t i = 0; i < row; ++i )
    delete ptr[i];

  // Free the array of pointers of DoubleSubscriptedArray
  delete[] ptr;
};

Array* DoubleSubscriptedArray::operator[]( const int subscript )
{
  if ( subscript < 0 || subscript >= row )
    throw std::out_of_range("Row subscript out of range.");

  return ptr[ subscript ]; 
};

Array* DoubleSubscriptedArray::operator[]( const int subscript ) const
{
  if ( subscript < 0 || subscript >= row )
    throw std::out_of_range("Row subscript out of range.");

  return ptr[ subscript ]; 
};

bool DoubleSubscriptedArray::operator==( const DoubleSubscriptedArray& other ) const
{
  if ( row != other.row || col != other.col )
    return false;

  for ( size_t i = 0; i < row; ++i )
    if ( ptr[i] != other.ptr[i] )
      return false;

  return true;
};

DoubleSubscriptedArray& DoubleSubscriptedArray::operator=( const DoubleSubscriptedArray& other )
{
  if ( this != &other )
  {
    size_t i;
    
    if ( row != other.row || col != other.col )
    {
      for ( i = 0; i < row; ++i )
        delete ptr[i];
      delete[] ptr;

      row = other.row;
      col = other.col;
      ptr = new Array*[row];

      for ( i = 0; i < row; ++i )
        ptr[i] = new Array(col);
    }

    for ( i = 0; i < row; ++i )
      ptr[i] = other.ptr[i];
  }

  return *this;
};

std::ostream &operator<<( std::ostream &out, const DoubleSubscriptedArray& a )
{
  for ( size_t i = 0; i < a.row; ++i )
    out << *(a.ptr[i]);
  return out;
}

std::istream &operator>>( std::istream &input, DoubleSubscriptedArray& a )
{
  for ( size_t i = 0; i < a.row; ++i )
    input >> *(a.ptr[i]);
  return input;
}

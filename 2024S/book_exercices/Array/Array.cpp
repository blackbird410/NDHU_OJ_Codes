#include <iostream>
#include "Array.h"

Array::Array( int _size ) 
  : size( _size > 0 ? _size : throw std::invalid_argument("Invalid array size.")), 
    ptr( new int[size] )
{
  for ( size_t i = 0; i < size; ++i)
    ptr[i] = 0;
};

Array::Array( const Array& other ) 
  : size( other.size ), 
    ptr( new int[size] ) 
{
  for ( size_t i = 0; i < size; ++i )
    ptr[i] = other.ptr[i];
}; 

Array::~Array () 
{
  delete[] ptr;
};

int& Array::operator[]( const int subscript )
{
  if ( subscript < 0 || subscript >= size )
    throw std::out_of_range("Subscript out of range.");

  return ptr[ subscript ]; // return an lvalue
};

int Array::operator[] ( const int subscript ) const
{
  if ( subscript < 0 || subscript >= size )
    throw std::out_of_range("Subscript out of range.");

  return ptr[ subscript ]; // return an rvalue
};

bool Array::operator==( const Array& other ) const 
{
  if ( size != other.size )
    return false;

  for ( size_t i = 0; i < size; ++i )
    if ( ptr[i] != other.ptr[i] )
      return false;

  return true;
};

Array& Array::operator=( const Array& other) 
{
  if ( this != &other ) // Avoids self assignment
  {
    if ( size != other.size )
    {
      delete[] ptr;
      size = other.size;
      ptr = new int[size];
    }

    for ( size_t i = 0; i < size; ++i )
      ptr[i] = other.ptr[i];
  }

  return *this;
};

std::ostream &operator<<( std::ostream &out, const Array& a )
{
  for ( size_t i = 0; i < a.size; ++i )
  {
    out << std::setw(4) << a.ptr[i];
    if ( (i + 1) % 10 == 0 ) out << std::endl;
  }
  if ( (a.size + 1) % 10 == 0 ) out << std::endl;

  return out;
};

std::istream &operator>>( std::istream &input, Array& a )
{
  for ( size_t i = 0; i < a.getSize(); ++i )
    input >> a.ptr[i];
  
  return input; // Allows std::cin >> a >> b; 
};


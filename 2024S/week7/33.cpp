#include <iostream>

#define MAXSIZE 100

template<class T>
class Set
{
public:
  Set() : count(0) {};
  Set( const Set<T> &other ) : count(0) 
  {
    size_t i;
    for (i = 0; i < other.count; ++i)
      add(other.element[i]);
  }

  bool contains( const T data ) const 
  {
    for ( size_t i = 0; i < count; ++i )
      if ( element[i] == data )
        return true;
    return false;
  }

  int add( const T data) 
  {
    if ( contains ( data ) || count == MAXSIZE ) 
        return 0;

    element[count] = data;
    count++;

    return 1;
  }

  int add( const Set<T> other )
  {
    size_t i = 0, nAdded = 0;
    for (i = 0; i < other.count; ++i)
       nAdded += add(other.element[i]);

    return nAdded;
  }

  Set operator+( const Set<T> &other )
  {
    Set<T> u(*this);
    u.add(other);

    return u; 
  }

  Set &operator=( const Set<T> &other)
  {
    count = 0;
    while ( count < other.count )
      add( other.element[count] );

    return *this;
  }

  Set operator-( const Set<T> &other )
  {
    Set<T> intersection;
    int minCount = ( count < other.count ) ? count : other.count;

    for ( size_t i = 0; i < minCount; ++i )
      if ( other.contains( element[i] ) )
        intersection.add( element[i] );

    return intersection;
  }
  
  void display()
  {
    int j;
    for(j = 0;j < count;j ++)
      std::cout<<element[j]<<" ";
  }

  friend std::ostream &operator<<( std::ostream &out, Set& s )
  {
    s.display();
    out << std::endl;

    return out;
  }
private:
  T element[MAXSIZE];
  int count;
};


int main() 
{
  Set <int> A;
  Set <int> B;

  A.add(1);
  A.add(2);
  A.add(3);
  A.add(4);
  B.add(4);
  B.add(5);
  B.add(6);

  B.add(A);
  A.add(7);

  std::cout << "A: " << A;
  std::cout << "B: " << B;

  Set<int> C = A + B;
  std::cout << "U: " << C;

  C = A - B;
  std::cout << "I: " << C;

  return 0;
}

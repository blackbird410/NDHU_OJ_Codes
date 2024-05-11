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
  
  void display()
  {
    int j;
    for(j = 0;j < count;j ++)
      std::cout<<element[j]<<" ";
  }
private:
  T element[MAXSIZE];
  int count;
};


int main() 
{
  Set <int> A;

  A.add(1);
  A.add(2);
  A.add(3);
  A.add(4);
  A.add(5);

  A.add(4);

  A.display();
  std::cout << std::endl;

  Set <int> B;
  B.add(6);
  B.add(A);
  B.display();
  std::cout << std::endl;

  Set<int> C(B);
  C.add(A);
  C.display();
  std::cout << std::endl;

  return 0;
}

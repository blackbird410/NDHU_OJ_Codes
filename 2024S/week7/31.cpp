#include <iostream>

template <typename T>
T* sort(T* array, int n)
{
  bool swapped = true;
  size_t i = 0;

  while(swapped)
  {
    swapped = false;
    for ( i = 0; i < n - 1; i++)
    {
      if ( array[i] > array[ i + 1] )
      {
        array[i] += array[i + 1];
        array[ i + 1 ] = array[ i ] - array[ i + 1 ];
        array[i] -= array[i + 1];
        swapped = true;
      }
    }
  }

  return array;
}

int main()
{
  int n = 4;
  int *a = new int[n];

  for ( size_t i = 0; i < n; ++i )
    a[i] = n - i;

  for (size_t i = 0; i < n; ++i )
    std::cout << a[i] << " ";
  std::cout << std::endl;

  sort(a, n);

  for (size_t i = 0; i < n; ++i )
    std::cout << a[i] << " ";

  delete[] a;

  return 0;
}

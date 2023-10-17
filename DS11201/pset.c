#include <stdio.h>
#include <stdlib.h>

void allocArray(int ***p, int m, int n);

int main()
{
  int **array, *a;
  int j, k;
  allocArray(&array, 5, 10);
  // for(j = 0;j < 5;j ++)
  //   for(k = 0;k < 10;k ++)
  //     array[j][k] = j * 10 + k;
  // for(j = 0;j < 5;j ++)
  //   for(k = 0;k < 10;k ++)
  //     printf("%p ", &(array[j][k]));
}

void allocArray(int ***p, int m, int n)
{
  printf("Adress: %p\n", p);
	// p = malloc((m * n + 1) * sizeof(p));
}

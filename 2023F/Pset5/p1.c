#include <stdio.h>

// Sort a series of numbers based on their modulus value
// If there is a tie between an odd number and an even number, odd number comes first
// If there is a tie between two odd numbers, the larger comes first
// If there is a tie between two even numbers, the smaller comes first

#define SIZE 10000

int canSwap(int a, int b, int m)
{
	int m1 = a % m, m2 = b % m;

	return (m1 > m2 || (m1 == m2 && ((!(a % 2) && b % 2) || (a % 2 && b % 2 && a < b) || (!(a % 2) && !(b % 2) && a > b))));
}

void swap(int *a, int *b)
{
	*a += *b;
	*b = *a - *b;
	*a -= *b;
}

void sort(int *arr, int n, int m)
{
	int i, j;

	for (i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			if (canSwap(arr[i], arr[j], m))
				swap(arr + i, arr + j);
}

void display(int *arr, int n, int m)
{
	int i;
	printf("%d %d\n", n, m);
	for (i = 0; i < n; i++)
		printf("%d\n", arr[i]);
}

int main()
{
	int n = 0, m = 0, i, arr[SIZE] = {0};

	while(scanf("%d %d", &n, &m) == 2 && n && m)
	{
		for (i = 0; i < n; i++)
			scanf("%d", &arr[i]);
		sort(arr, n, m);
		display(arr, n, m);
	}
	printf("0 0");

	return 0;
}

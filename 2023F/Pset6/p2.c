#include <stdio.h>

// Write a program to convert an integer to a binary
#define SIZE 10000

int convert(int *arr, int n);

int main()
{
	int n = 0, i = 0; 
	int arr[SIZE] = {0};

	scanf("%d", &n);

	n = convert(arr, n);

	for (i = n - 1; i >= 0; i--)
		printf("%d", arr[i]);
	
	return 0;
}

int convert(int *arr, int n)
{
	int i = 0;

	while(n)
	{
		if (n == 1)
		{
			arr[i] = 1;
			n = 0;
		}
		else
		{
			// Find the remainder and save it as the latest digit
			arr[i] = n % 2;

			// [Reduce]: n -> n / 2
			n /= 2; 
		}
		i++;
	}

	return i;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 1000

int main()
{
	// Initalize n, trunc_mean, sum  variables
	int n = 0, i = 0, j = 0, arr[SIZE] = {0};
	float trunc_mean = 0, sum = 0;

	scanf("%d", &n);

	// Take the n  integers until the enter character is given
	for(i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	// Sort the list (Bubble sort)
	int swapped = 0;
	int temp = 0;
	do 
	{
		swapped = 0;
		for (i = 0; i < n - 1; i++)
		{
			if (arr[i] > arr[i+1])
			{
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				swapped = 1;
			}
		}
	}while(swapped);

	// Compute the sum
	// Start the loop at 3 and end at lenght -3
	for (i = 3; i < n - 3; i++)
	{
		sum += arr[i];
	}

	// Divide the sum by N - 6
	trunc_mean = sum / (n - 6);

	// Return the value round down to two decimal point
	printf("%.2f", trunc_mean);

	return 0;
}

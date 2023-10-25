#include <stdio.h>

#define SIZE 50

int sort(int *arr, int n);

int main()
{
	// Take inputs N: number of test cases
	// Test cases: one integer (p) and one array (arr(p))
	int arr[SIZE] = {0}, i = 0, j = 0, n = 0, p = 0;

	scanf("%d", &n);

	for(i = 0; i < n; i++)
	{
		scanf("%d", &p);
		// Take the array input
		for(j = 0; j < p; j++)
		{
			scanf("%d", &arr[j]);
		}

		// Sort each array and return the number of swapp
		printf("Optimal train swapping take %d swaps.\n", sort(arr, p));
	}

	return 0;
}

int sort(int *arr, int n)
{
	// Bubble sort
	int swapped = 0, i = 0, temp = 0, counter = 0;
	while(1)
	{
		swapped = 0;
		for(i = 0; i < n-1; i++)
		{
			if (arr[i] > arr[i+1])
			{
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				swapped = 1;
				counter++;
			}
		}

		if (!swapped)
			break;
	}

	return counter;
}

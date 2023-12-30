#include <stdio.h>

// Find the number of swaps required to sort an array

#define SIZE 50

int sort(int *arr, int n)
{
	int count = 0, swapped = 1, i = 0;

	while(swapped)
	{
		swapped = 0;

		for (i = n-1; i > 0; i--)
		{
			if (arr[i - 1] > arr[i])
			{
				arr[i - 1] += arr[i];
				arr[i] = arr[i - 1] - arr[i];
				arr[i - 1] -= arr[i];
				swapped = 1;
				count++;
			}
		}
	}

	return count;
}

int main()
{
	int test_cases = 0, n, i, arr[SIZE] = {0};

	scanf("%d", &test_cases);
	while(test_cases--)
	{
		scanf("%d", &n);
		for (i = 0; i < n; i++)
			scanf("%d", &arr[i]);
		printf("Optimal train swapping takes %d swaps.\n", sort(arr, n));
	}

	return 0;
}

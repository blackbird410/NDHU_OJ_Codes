#include <stdio.h>
#include <math.h>

#define SIZE 10000

int is_prime(int n);
void sort(int *arr, int n);


int main()
{
	int n = 0, i = 0, value = 0, arr[SIZE] = {0};
	
	scanf("%d", &n);

	for (i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	// Sort the array in the required order of primarity
	sort(arr, n);

	// Display the result
	for (i = 0; i < n - 1; i++)
		printf("%d ", arr[i]);
	printf("%d", arr[i]);
		
	return 0;
}

int is_prime(int n)
{
	int i = 0;
	if (n < 2)
		return 0;

	for(i = 2; i*i <= n; i++)
	{
		if (n % i == 0)
			return 0;
	}

	return 1;
}

void sort(int *arr, int n)
{
	int swapped = 1, i = 0, temp = 0;

	while(swapped)
	{
		swapped = 0;

		for (i = 0; i < n - 1; i++)
		{
			if (!is_prime(arr[i]) && is_prime(arr[i+1]))
			{
				// A non-prime and a prime number
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				swapped = 1;
			}
			else if (arr[i] < arr[i + 1] && (is_prime(arr[i]) && is_prime(arr[i + 1])))
			{
				// Two prime numbers: Greater number comes first
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				swapped = 1;
			}
			else if (arr[i] > arr[i+1] && (!is_prime(arr[i]) && !is_prime(arr[i+1])))
			{
				// Two non-primes: Smaller number come first
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				swapped = 1;
			}
		}
	}
}

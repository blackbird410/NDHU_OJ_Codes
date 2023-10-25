#include <stdio.h>

#define SIZE 10000

void sort(int *arr, int n, int m);

int main()
{
	// Inputs: N numbers and M a positive integer
	// Outputs: A sorted list of the N numbers in ascending order of their modulo M value.
	
	int n = 0, i = 0, m = 0, arr[SIZE];
	
	// Take the inputs N and M until N = 0 and M = 0 
	while(1)
	{
		scanf("%d %d", &n, &m);
		// Check for the end of inputs
		if (!n && !m)
			break;

		// Take the N values into the array
		for(i = 0; i < n; i++)
		{
			scanf("%d", &arr[i]);
		}

		// Sort the numbers per the requirements
		sort(arr, n, m);

		// Output the result
		printf("%d %d\n", n, m);
		for (i = 0; i < n; i++)
		{
			printf("%d\n", arr[i]);
		}
	}

	printf("%d %d", n, m);

	return 0;
}

void sort(int *arr, int n, int m)
{
	// Here we sort the array given by the following requirements:
	// Requirements: 
        // - If there is a tie between an odd number and an even number, the odd value precede the even number
        // - If there is a tie between two odd numbers, the larger odd number will precede the smaller odd number
        // - If there is a tie between two even numbers, the smaller even number will precede the larger even number
        // Reminder: The value of negative numbers can never have a modulus greater than zero.
	
	int i = 0, j = 0, temp = 0, odd = 0, even = 0, mod1 = 0, mod2 = 0;

	for (i = 0; i < n; i++)
	{
		// Find the correct place of the current number
		for(j = i + 1; j < n; j++)
		{	
			mod1 = arr[i] % m;
			mod2 = arr[j] % m;
			// Compare the modulo M of each number
			if ((arr[i] % m) > (arr[j] % m))
			{
				temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			else if((arr[i] % m) == (arr[j] % m))
			{
				if ((arr[i] % 2 && !(arr[j] % 2)) || (arr[j] % 2 && !(arr[i] % 2)))
				{
					// Here we have an odd number and an even number
					if (arr[i] % 2)
					{
						odd = arr[i];
						even = arr[j];
					}
					else
					{
						odd = arr[j];
						even = arr[i];
					}

					// The odd value precede the even number
					arr[i] = odd;
					arr[j] = even;
				}
				else if (arr[i] % 2 && arr[j] % 2)
				{
					// Here we have two odd numbers
					
					// The larger odd number will precede the smaller odd number
					if (arr[i] < arr[j])
					{
						temp = arr[i];
						arr[i] = arr[j];
						arr[j] = temp;
					}
				}
				else
				{
					// Here we have two even numbers

					// The smaller even number will precede the larger even number
					if (arr[i] > arr[j])
					{
						temp = arr[i];
						arr[i] = arr[j];
						arr[j] = temp;
					}
				}
			}

		}
	}
}

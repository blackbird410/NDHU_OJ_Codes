#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 1000

int main()
{
	// Initialize an N variable and a mean variable
	int n = 0, i = 0, counter = 0;
	double mean = 0, sum = 0;
	
	// Take the N value
	scanf("%d", &n);

	// Create an array for storing the N integer values
	int arr[SIZE] = {0};

	// Take the values as inputs
	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	// Compute the sum of all values
	for (i = 0; i < n; i++)
	{
		sum += arr[i];
	}

	// Compute the mean
	mean = sum / n;

	// Count the number of failing students
    for (i = 0; i < n; i++)
    {
        if (arr[i] < mean)
        {
            counter++;
        }
    }

	// Return the standard deviation with two decimal point
	printf("%d", counter);
}

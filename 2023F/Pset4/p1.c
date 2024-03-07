#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 1000

int main()
{
	// Initialize an N variable, a mean variable and a standard deviation
	int n = 0, i = 0;
	double mean = 0, std = 0, sum = 0;
	
	// Take the N value
	scanf("%d", &n);

	// Create an array for storing the N integer values
	int arr[SIZE] = {0};

	// Take the values as inputs
	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
		sum += arr[i];
	}

	// Compute the mean
	mean = sum / n;

	// Compute the standard deviation
	for (i = 0; i < n; i++)
	{
		std += pow((arr[i] - mean), 2); 
	}
	std = sqrt(std / n); 

	// Return the standard deviation with two decimal point
	printf("%.2f", std);
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Input: Several blocks of numbers, starting with N (0 < N <= 1000000) as number of numbers X to follow (X < 65536)
// Input is terminated by end of file
// Output: One line that will contain: 
// - the minimum value for A (lock combination)
// - the number of inputs that satisfy the property of A
// - how many possible DIFFERENT integer values are there for A. (It is possible that those values are not in the input)

#define SIZE 1000000

void sort(int *arr, int n);
int minAbsDev(int *arr, int n, int a);

int main()
{
	int arr[SIZE] = {0};
	int n = 0, i = 0, temp = 0, counter = 0, median = 0, mean = 0, minDev = 0, minValue = 0, pVal = 0, min = 0;
	float sum = 0, t = 0;

	// Take a block of input until the end of file 
	while(1)
	{
		n = 0;
		// Take the N value
		scanf("%d", &n);

		// Check for end of file
		if (!n)
		       break;
			
		// Take the X numbers into the array 
		sum = 0;
		for (i = 0; i < n; i++)
		{
			scanf("%d", &arr[i]);
			sum +=  arr[i];	
		}

		// Sort the array
		sort(arr, n);

		// Find the median 
		median = arr[(n / 2)- 1];
		minValue = median;

		// Find the mean
		t = sum / n;
		mean = round(t);

		// Compute the summation of minimum absolute deviation
		if (mean != median)
		{
			minDev = minAbsDev(arr, n, median);
			temp = minAbsDev(arr, n, mean);
			if (temp < minDev)
			{
				minDev = temp;
				minValue = mean;
			}
		}else
		{
			minDev = minAbsDev(arr, n, median);
		}

		// Find all the values that satisfies the property of A
		temp = (mean < median) ? median : mean;
		min = (mean < median) ? mean : median;

		for (pVal = 0, i = min; i < temp + 1; i++)
		{
			sum = minAbsDev(arr, n, i);
			if (minDev == sum)
				pVal++;
			else if(minDev > sum)
			{
				minValue = i;
				minDev = sum;
				pVal = 1;
			}
		}

		// Count all the inputs that are possible values
		for (counter = 0, i = 0; i < n; i++)
		{
			sum = minAbsDev(arr, n, arr[i]);
			if (sum == minDev)
				counter++;
		}

		printf("%d %d %d\n", minValue, counter, pVal);
	}
}

void sort(int *arr, int n)
{
	int i = 0, flag = 1, temp = 0;

	while(flag)
	{
		flag = 0;
		for(i = 0; i < n - 1; i++)
		{
			if (arr[i] > arr[i+1])
			{
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				flag = 1;
			}
		}
	}
}

int minAbsDev(int *arr, int n, int a)
{
	int i = 0, sum = 0;
	for (i = 0; i < n; i++)
	{
		sum += abs(arr[i] - a);
	}

	return sum;
}


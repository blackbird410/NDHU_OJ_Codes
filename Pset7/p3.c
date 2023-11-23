#include <stdio.h>
#include <math.h>

#define SIZE 100

void sort(int (*arr)[2], int n);
double  getSize(int (*arr)[2], int n, int max_height);

int main()
{
	int c = 0, n = 0, i = 0, max_height = 0;
	int arr[SIZE][2] = {0};
	double size = 0;
	
	// Take the number of test cases
	scanf("%d", &c);

	while(c--)
	{
		// Take the number of coordinates
		scanf("%d", &n);

		max_height = 0;

		// Take the coordinates and recording the maximum height
		for(i = 0; i < n; i++)
		{
			scanf("%d %d", &arr[i][0], &arr[i][1]);
			max_height = (arr[i][1] > max_height) ? arr[i][1] : max_height;
		}

		// Sort the coordinates in descending order by x-values
		sort(arr, n);

		// Compute the size of the mountainsides
		size =  getSize(arr, n, max_height);

		// Output the size
		printf("%.2lf\n", size);
	}

	return 0;
}

void sort(int (*arr)[2], int n)
{
	int i = 0, swapped = 0;

	do
	{
		swapped = 0;
		for (i = 0; i < n-1; i++)
		{
			if (arr[i][0] < arr[i+1][0])
			{
				arr[i][0] += arr[i+1][0];
				arr[i+1][0] = arr[i][0] - arr[i+1][0];
				arr[i][0] -= arr[i+1][0];

				arr[i][1] += arr[i+1][1];
                                arr[i+1][1] = arr[i][1] - arr[i+1][1];
                                arr[i][1] -= arr[i+1][1];	
				
				swapped = 1;
			}
		}

	} while(swapped);
}

double getSize(int (*arr)[2], int n, int max_height)
{
	int i = 0, y_max = 0, x_c, x_p, y_c, y_p;
	double sum = 0;

	for (i = 1; i < n; i++)
	{
		x_c = arr[i][0];
		x_p = arr[i-1][0];
		y_c = arr[i][1];
		y_p = arr[i-1][1];

		if (y_max == max_height)
			break;

		// Is y_max > y_i+1 ?
		if (y_c > y_max)
		{
			sum += sqrt(pow(y_c - y_p, 2) + pow(x_p - x_c, 2)) - sqrt(pow(y_max - y_p, 2) * (1 + pow(x_p - x_c, 2) / pow(y_c - y_p, 2)));
			y_max = arr[i][1];
		}
	}

	return sum;
}

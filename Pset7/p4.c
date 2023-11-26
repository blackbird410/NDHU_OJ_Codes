#include <stdio.h>

#define SIZE 100

void initArray(int *arr, int n);
int getSurvivor(int *arr, int n, int k, int i);
void printArray(int *arr, int n);

int main()
{
	// The goal is not to find the survivor, but to find the position counting should start so YOU (1) can survive
	// Find k such that 1 is the survivor

	int n = 0, k = 1, i = 0, arr[SIZE];
	
	while(scanf("%d %d", &n, &k) == 2 && (n  || k))
	{
		initArray(arr, n);
		while(getSurvivor(arr, n, k, i) != 1 && i < n)
		{
			initArray(arr, n);
			i++;
		}
		printf("%d\n", i+1);
	}
	
	return 0;
}

void initArray(int *arr, int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
		arr[i] = i + 1;
}

void shift(int *arr, int n, int k)
{
	int i = 0;

	for (i = k; i < n-1; i++)
		arr[i] = arr[i+1];
}

int getSurvivor(int *arr, int n, int k, int i)
{
	int dead = 0;

	if (n == 1)
		return arr[0];
	
	printArray(arr, n);

	i = i + k - 1;
	if (i >= n)
		i = (i % n);

	dead = i;
	i = i + k;
	if (i >= n)
		i = (i % n);

	arr[dead] = arr[i];

	if (i < n - 1)
		shift(arr, n, i);
	n--;

	// TODO: Ensure that the starting position is always to the left of the dead
	if (n <= k)
		i = dead;
	else if(dead == 0)
		i = 1;
	else if (dead == n)
		i = 0;
	else
		i = dead + 1; 

	return getSurvivor(arr, n, k, i);

}

void printArray(int *arr, int n)
{
	int i = 0;
	printf("Array:");
	for (i = 0; i < n; i++)
		printf(" %d", arr[i]);
	printf("\n");
}

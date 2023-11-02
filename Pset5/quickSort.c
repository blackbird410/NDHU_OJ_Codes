#include <stdio.h>

#define SIZE 1000

void quickSort(int *arr, int low, int high);
int partition(int *arr, int low, int high);

int main()
{
	int arr[SIZE], n = 0, i = 0;

	printf("How much numbers ? ");
	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		scanf("%d", &arr[i]);
	}

	quickSort(arr, 0, n-1);

	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}

void quickSort(int *arr, int low, int high)
{
	int pi = 0;

	// When low is less than high
	if (low < high)
	{
		// Find the pivot element such that :
		// element smaller than the pivot are on the left
		// element greater than the pivot are on the right
		pi = partition(arr, low, high);

		// Recursive call on the left of the pivot
		quickSort(arr, low, pi - 1);

		// Recursive call on the right of the pivot
		quickSort(arr, pi + 1, high);
	}
}

int partition(int *arr, int low, int high)
{
	int pivot = 0, i = 0, j = 0, temp = 0;

	// Choose the pivot as the rightmost element
	pivot = arr[high];

	// Pointer for  greater element
	i = low - 1;

	for(j = low; j <= high; j++)
	{
		// If the current element is smaller than the pivot
		if (arr[j] < pivot)
		{
			// Increment index of smaller element
			i++;
			// swap(&arr[i], &arr[j]);
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}	
	// Swap the greater element specified by i in the list with the pivot
	// swap(&arr[i+1], &arr[high]);
	temp = arr[i+1];
	arr[i+1] = arr[high];
	arr[high] = temp;

	return (i+1);
}


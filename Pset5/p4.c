#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000005

void quickSort(int *arr, int low, int high);
int partition(int *arr, int low, int high);

int main ()
{
    int arr[SIZE] = {0}, i = 0, j = 0, n = 0, mid1 = 0, mid2 = 0, counter = 0, pVal = 0;

    while(scanf("%d", &n) != EOF)
    {
        // if(!n)
        //     break;
        
        for (i = 0; i < n; i++)
            scanf("%d", &arr[i]);

        quickSort(arr, 0, n - 1);

	mid1 = arr[(n - 1)/2];
	mid2 = arr[n / 2];
        
        counter = 0;
        pVal = 0;
        for(i = 0; i < n; i++)
        {
            if (arr[i] == mid1 ||arr[i] == mid2)
                counter++;
        }
        printf("%d %d %d\n", mid1, counter, mid2 - mid1 + 1);
    }

    return 0;

}

void quickSort(int *arr, int low, int high)
{
    int p = 0;

    if (low < high)
    {
        p = partition(arr, low, high);

        quickSort(arr, low, p - 1);
        
        quickSort(arr, p + 1, high);
    }
}

int partition(int *arr, int low, int high)
{
    int pivot = 0, i = 0, j = 0, temp = 0;

    pivot = arr[high];

    i = (low - 1);

    for (j = low; j <= high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;

            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    } 
    temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;

    return (i+1);
}


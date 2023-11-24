#include <stdio.h>

#define SIZE 100
void initArray(int *arr, int n);
int getLuckyNumber(int *arr, int n, int k);
int isNotEnd(int *arr, int n);
int getNumber(int *arr, int n);

int main()
{
    int i = 0, n = 0, k = 1;
    int arr[SIZE];

    initArray(arr, n);

    while(scanf("%d %d", &n, &k) == 2 && (n  || k))
    {
        printf("%d\n", getLuckyNumber(arr, n, k));
    }

    return 0;
}

void initArray(int *arr, int n)
{
    int i = 0;
    for (i = 0; i < n; i++)
        arr[i] = i + 1;
}

int getLuckyNumber(int *arr, int n, int k)
{
    int p = 0, i = 0;

    while(isNotEnd(arr, n))
    {
        if (p == n)
            p = 0;
        // We start counting from k the person to be person killed
        for (i = 0; i < n; i++)
        {
            // TODO: Continue here
            if (arr[i] > 0)
            {
                p++;

            }
        }
        // When we find the one to kill, we set its value to -1
    }

    return getNumber(arr, n);

}

int isNotEnd(int *arr, int n)
{
    int count = 0, i;

    for(i = 0; i < n; i++)
    {
        if (count >= 2)
            return 1;
        if (arr[i] > 0)
            count++;
    }

    return 0;

}

int getNumber(int *arr, int n)
{
    int i = 0;
    
    for (i = 0; i < n; i++)
    {
        if (arr[i] > 0)
            return arr[i];
    }

    return 0;
}
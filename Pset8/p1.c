#include <stdio.h>

#define SIZE 100

void takeInput(int (*arr)[SIZE], int k);
void outputMatrix(int (*arr)[SIZE], int n, int m);

int main()
{
    int n, m, k;
    int arr[SIZE][SIZE] = {0};

    scanf("%d %d %d", &n, &m, &k);
    takeInput(arr, k);
    outputMatrix(arr, n, m);

    return 0;
}

void takeInput(int (*arr)[SIZE], int k)
{
    int i = 0, j = 0, v = 0;

    while(k--)
    {
        scanf("%d %d %d", &i, &j, &v);
        arr[i][j] = v;
    }
}

void outputMatrix(int (*arr)[SIZE], int n, int m)
{
    int i = 0, j = 0;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }
}
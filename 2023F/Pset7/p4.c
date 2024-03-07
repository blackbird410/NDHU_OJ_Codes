#include <stdio.h>

#define SIZE 101

void initArray(int *arr, int n);
int getSurvivor(int *arr, int n, int k);

int main() 
{
    int n, k, i = 0, arr[SIZE];

    while (scanf("%d %d", &n, &k) == 2 && n && k) 
    {
        initArray(arr, n);

        i = getSurvivor(arr, n, k);
        i = (i == 1) ? i : n + 2 - i;

        printf("%d\n", i);
    }

    return 0;
}

void initArray(int *arr, int n)
{
	int i = 0;
	for (i = 0; i < n; i++)
		arr[i] = i + 1;
}


int getSurvivor(int *arr, int n, int k)
{
    int dead = 0, pos = 0, counter, total = n;

    while(total > 1)
    {
        counter = 0;

        while(1)
        {
            if (arr[pos])
                counter++;
            if (counter == k)
                break;
            
            pos = (pos + 1) % n;
        }

        dead = pos;
        arr[dead] = 0;
        total--;

        counter = 0;
        pos = (pos + 1) % n; 
        while (1)
        {
            if (arr[pos])
                counter++;
            if (counter == k)
                break;
            
            pos = (pos + 1) % n;
        }

        arr[dead] = arr[pos];
        arr[pos] = 0;

        pos = (dead + 1) % n;
    }

    return arr[dead];
}

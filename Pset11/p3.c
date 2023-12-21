#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000

int lookAndSay(int n, char *arr, int *count);

int main()
{
    int n;
    char arr[SIZE];
    int count[SIZE] = {0};

    scanf("%d", &n);
    lookAndSay(n, arr, count);

    printf("%s\n", arr);

    return 0;
}

int lookAndSay(int n, char *number, int *count)
{
    if (n == 1)
    {
        number[0] = '1';
        number[1] = '\0';
        return 0;
    }

    // Read the number
    lookAndSay(n - 1, number, count);
    printf("%s\n", number);

    char arr[SIZE];
    int i = 0, j = 0, k = 0;
    while (count[i])
    {
        count[i] = 0;
        i++;
    }
    i = 0;

    // Recording the frequency
    arr[i] = number[j];
    while(number[j] != '\0')
    {
        if (arr[i] != number[j])
        {
            i++;
            arr[i] = number[j];
        }

        count[i]++;
        j++;
    }

    // Adding the frequency and the number
    j = 0;
    while(k <= i)
    {
        number[j] = count[k] + '0';
        number[j + 1] = arr[k];
        j += 2;
        k++;
    }
    number[j] = '\0';

    return 0;
}
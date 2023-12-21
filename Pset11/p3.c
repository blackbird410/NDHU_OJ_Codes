#include <stdio.h>
#include <stdlib.h>

#define SIZE 100000

char *lookAndSay(int n);

int main()
{
    int n;
    scanf("%d", &n);

    char *p = lookAndSay(n);

    printf("%s\n", p);
    free(p);

    return 0;
}

char *lookAndSay(int n)
{
    char *arr = malloc(SIZE * sizeof(char));
    if (arr == NULL)
        return NULL;

    if (n == 1)
    {
        arr[0] = '1';
        arr[1] = '\0';
        return arr;
    }
    // Read the number
    char *number = lookAndSay(n - 1);
    printf("%s\n", number);

    int i = 0, j = 0;
    int count[SIZE] = {0};

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

    int k = 0;
    
    j = 0;
    while(k <= i)
    {
        number[j] = count[k] + '0';
        number[j + 1] = arr[k];
        j += 2;
        k++;
    }
    number[j] = '\0';
    free(arr);

    return number;
}

// 1
// 11
// 21
// 1211
// 111221
// 312211
// 13112221
// 1113213211
// 31131211131221
// 13211311123113112211
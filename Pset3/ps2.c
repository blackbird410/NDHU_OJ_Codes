#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i = 0, max = 0;
    int list[4];

    // Take the inputs
    scanf("%d %d %d %d", &list[0], &list[1], &list[2], &list[3]);
    max = list[0];

    // Find the maximum
    for (i = 1; i < 4; i++)
    {
        if (list[i] > max)
        {
            max = list[i];
        }
    }
    
    // Show the maximum
    printf("%d", max);

    return 0;
}
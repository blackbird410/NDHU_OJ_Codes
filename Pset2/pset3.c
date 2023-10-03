#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Take 4 integer as input
    int a1, a2, b1, b2;
    scanf("%d %d %d %d", &a1, &a2, &b1, &b2);

    // Re-sorting the values
    if(a1 > a2)
    {
        // Swapping the values
        int temp = a1;
        a1 = a2;
        a2 = temp;
    }

    if(b1 > b2)
    {
        // Swapping the values
        int temp = b1;
        b1 = b2;
        b2 = temp;
    }

    // Check if they are overlay or not
    if (a2 > b1)
    {
        printf("overlay");
    }
    else
    {
        printf("no overlay");
    }

    return 0;

}
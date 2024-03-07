#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Take three integer inputs
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    // Check if we can construct a triangle
    if (a + b <= c)
    {
        printf("can not construct");
        return 0;
    } 

    // Check the kind of triangle
    if ((a * a + b * b) == c * c)
    {
        printf("right triangle");
        return 0;
    }
    else if ((a * a + b * b) > c * c)
    {
        printf("acute triangle");
        return 0;
    }
    else 
    {
        printf("obtuse triangle");
        return 0;
    }

    return 0;
}
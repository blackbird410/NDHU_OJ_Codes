#include <stdio.h>
#include <stdlib.h>

int main()
{
    int plate_number = 0;

    // Take the input
    scanf("%d", &plate_number);

    // Get the modulo by 10 until n <= 0
    while (plate_number > 0)
    {
        if (plate_number % 10 == 4)
        {
            printf("Yes");
            return 0;
        }
        plate_number /= 10;
    } 

    printf("No");

    return 0;
}
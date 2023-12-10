#include <stdio.h>
#include <stdlib.h>

#define ASCII_LOWER_BOUND 48


int main()
{
    // Read a 4 digits
    int n = 0, i = 0;
    char reverse[10];
    scanf("%d", &n);

    // Reverse the digits
    for (i = 0; i < 4; i++)
    {
        // Take the end digit of the number 
        reverse[i] = (n % 10) + ASCII_LOWER_BOUND;
        n /= 10; 
    }

    // End the string
    reverse[4] = '\0';

    // Display  the number
    printf("%s", reverse);

    return 0;
}
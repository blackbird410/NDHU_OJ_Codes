#include <stdio.h>


int main()
{
    // Initialize the variables
    int x = 0, y = 0, z = 0;

    // Read the values
    scanf("%d %d %d", &x, &y, &z);

    // Compute the average
    float avg = (x + y + z) / 3.0;

    // Print the average
    printf("%f", avg);
        
    return 0;
}
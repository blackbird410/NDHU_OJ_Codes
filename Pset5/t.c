#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n = 10, mean = 0;
    float sum = 59.01, t = 0;  

    t = sum / (float) n;  // Casting n to float for correct division.
    printf("%f", round(sum));
    
    // mean = round(t);
    // printf("Mean: %d\n", mean);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    // Take a float input
    float user_input = 0;
    scanf("%f", &user_input);

    // Print the value round off and down 
    printf("%.2f\n%.2f", round(user_input * 100) / 100, floor(user_input * 100) / 100);

    return 0;
}
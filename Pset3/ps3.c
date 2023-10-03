#include <stdio.h>
#include <stdlib.h>

int main()
{
    int distance = 0;
    float total_toll = 0;

    // Take the distance input
    scanf("%d", &distance);

    // Check if it's greater than 200
    if (distance > 200)
    {
        // Get the amount to apply discount
        int discount_prop = distance - 200;

        // Get the total toll
        total_toll = (discount_prop * 0.75 + 200) * 1.2;
    }
    else
    {
        total_toll = distance * 1.2;
    }

    printf("%.0f", total_toll);
}
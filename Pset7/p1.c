#include <stdio.h>

int maxCycle(int n);

int main()
{
    // Set a max variable for max cycle
    int max_cycle = 0, i = 0, j = 0, k = 0, cycle = 0;

    while(1)
    {
        i = 0, j = 0, max_cycle = 0;
        scanf("%d %d", &i, &j);
        if (!i || !j)
            break;
        printf("\n");

        // Compute max-cycle for all numbers between i and j
        for (k = i; k < j; k++)
        {
            // Update the max when the current cycle-length > max-cycle
            cycle = maxCycle(k);
            if (cycle > max_cycle)
                max_cycle = cycle;
        }
        
        // Output : i, j max-cycle
        printf("%d %d %d", i, j, max_cycle);
    }

    return 0;
}

int maxCycle(int n)
{
    // Apply the algorithm to return the maximum cycle for a number n
    // What is the maximum_cycle ?
    // It is how much numbers you can find from n until 1 is returned.

    // printf("%d ", n);

    if (n == 1)
    {
        // Base case
        return 1;
    }
    else if (n % 2)
    {
        return maxCycle(3*n + 1) + 1;
    }
    else 
    {
        return maxCycle(n/2) + 1;
    }
}
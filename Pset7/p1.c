#include <stdio.h>

unsigned long maxCycle(unsigned long n);

int main()
{
    // Set a max variable for max cycle
    unsigned long max_cycle = 0, i = 0, j = 0, k = 0, cycle = 1;

    while(scanf("%ld %ld", &i, &j) == 2)
    {
        printf("%ld %ld", i, j);

        //  Swap the numbers if i > j
        if (i > j)
        {
            i += j;
            j = i - j;
            i -= j;
        }
        
        max_cycle = 0;

        // Compute max-cycle for all numbers between i and j
        for (k = i; k <= j; k++)
        {
            // Update the max when the current cycle-length > max-cycle
            cycle = maxCycle(k);
            max_cycle = (cycle > max_cycle) ? cycle : max_cycle;
        }
        
        // Output max-cycle
        printf(" %ld\n", max_cycle);
    }

    return 0;
}

unsigned long maxCycle(unsigned long n)
{
    // Apply the algorithm to return the maximum cycle for a number n
    // What is the maximum_cycle ?
    // It is how much numbers you can find from n until 1 is returned.

    // printf("%d ", n);

    // Recursive method
    // -------------------
    if (n == 1)
    {
        // Base case
        return 1;
    }
    else if (n % 2)
    {
        return maxCycle((3*n) + 1) + 1;
    }
    else 
    {
        return maxCycle(n / 2) + 1;
    }

    // Iterative method
    // -----------------
    // int cycle = 0;
    // do 
    // {
    //     if (n == 1)
    //     {
    //         break;
    //     }
    //     else if (n % 2)
    //     {
    //         n = 3 * n + 1;
    //     }
    //     else
    //     {
    //         n /= 2;
    //     }
    //     cycle++;
    
    // }while (n > 0);

    // return cycle;
}

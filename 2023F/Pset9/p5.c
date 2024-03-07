#include <stdio.h>

int main() 
{
    int *a, *b;
    init(&a, &b);
    int sum = 0, i;
    
    //add your code here
    for (i = 0; (a + i) < b; i++)
        sum += *(a + i);
    
    printf("%d", sum);
    
    return 0;
}
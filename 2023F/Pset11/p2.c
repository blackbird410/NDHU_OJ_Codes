#include<stdio.h>

#define SIZE 1000

/*************************************************************
function name: convertToDifferentBase
description: Convert a decimal number @dec to the number with different @base and store the result as a string in result
return vaule: Result after convert.
notice: The letter you see in the number should be upper case.
*************************************************************/

char *convertToDifferentBase(int dec, int base, char *result) 
{
    int remainder, isNegative = 0, i = 0;
    char r[SIZE];

    if (dec < 0)
        isNegative = 1;
    
    dec = (dec  < 0) ?  -dec : dec;

    // Convert the decimal number in the base specified
    while(dec)
    {
        remainder = dec % base;
        r[i] = (remainder > 9) ? remainder + '7' : remainder + '0';
        dec /= base; 

        i++;
    }

    int l = i - 1;
    if (isNegative)
        result[0] = '-';

    for(i = isNegative; i <= l + isNegative; i++)
    {
        result[i] = r[l - i + isNegative];
    }

    result[i] = '\0';

    return result;
}

int main()
{
    int n, d;
    char result[SIZE], *p;

    p = result;

    while(scanf("%d %d", &n,  &d) == 2 && n && d)
    {   
        p = convertToDifferentBase(n, d, p);
        printf("%s\n", p);
    }
    
    return 0;
}
#include <stdio.h>

#define SIZE 1000

/*************************************************************
function name: convertToDifferentBase
description: Convert a decimal number @dec to the number with different @base and store the result as a string in result
return vaule: Result after convert.
notice: The letter you see in the number should be upper case.
*************************************************************/

char *convertToDifferentBase(int dec, int base, char *result) 
{
    if (!(dec / base))
    {
        if (dec < 0)
        {
            result[0] = '-';
            result[1] = (abs(dec % base) > 9) ? abs(dec % base) + '7': abs(dec % base) + '0';
            result[2] = '\0';
        }
        else
        {
            result[0] = (abs(dec % base) > 9) ? abs(dec % base) + '7': abs(dec % base) + '0';
            result[1] = '\0';
        }
        
        return result; 
    }    
    
    convertToDifferentBase(dec / base, base, result);
    int digit = (abs(dec % base) > 9) ? abs(dec % base) + '7': abs(dec % base) + '0';
    int i = 0;
    for (i = 0; result[i] != '\0'; i++);
    result[i] = digit;
    result[i+1] = '\0';
    return result;
}

int main()
{
    int dec = 0, base = 0;
    char result[SIZE];

    while(scanf("%d %d", &dec, &base) == 2 && dec && base)
    {
        convertToDifferentBase(dec, base, result);
        printf("%s\n", result);
    }

    return 0;
}

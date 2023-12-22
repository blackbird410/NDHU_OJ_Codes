#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000

/*************************************************************
function name: convertToDifferentBase
description: Convert a decimal number @dec to the number with different @base and store the result as a string in result
return vaule: Result after convert.
notice: The letter you see in the number should be upper case.
*************************************************************/
char *shiftAdd(char *result, char r)
{
    int i, l = strlen(result);
    if (!l)
    {
        result[0] = r;
        result[1] = '\0';
        return result;
    }

    // Shift the result and add the new digit
    result[l + 1] = '\0';
    for (i = l; i > 0; i--)
        result[i] = result[i - 1];
    result[0] = r;

    return result;
}

char *convertToDifferentBase(int dec, int base, char *result) 
{
    if (!dec)
        return result;
    
    int r = abs(dec % base);
    r = (r > 9) ? r + '7' : r + '0';
    shiftAdd(result, (char) r);

    if (dec < 0 && !(dec / base))
        shiftAdd(result, '-');

    return convertToDifferentBase(dec / base, base, result);
}

int main()
{
    int dec = 0, base = 0;
    char result[SIZE];

    while(scanf("%d %d", &dec, &base) == 2 && dec && base)
    {
        result[0] = '\0';
        convertToDifferentBase(dec, base, result);
        printf("%s\n", result);
    }

    return 0;
}

// 10     2     1010
// 25     3     2201
// 123     4     3003
// 100     5     2020
// 1024     8 10000000
//     0    10        0
// -10     2    -1010
// -25     3    -2201
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

char *reverse(char *result)
{
    int l = strlen(result), i = 0;

    while(i < l/2)
    {
        result[i] += result[l - i - 1];
        result[l - i - 1] = result[i] - result[l - i - 1];
        result[i] -= result[l - i - 1];

        i++;  
    }

    return result;
}

int isNum(char c)
{
    return (c >= '0' && c <= '9');
}

char *convertToDifferentBase(int dec, int base, char *result) 
{
    if (!dec)
    {
        reverse(result);
        return result;
    }
    
    int r = abs(dec % base);
    int l = (isNum(result[0])) ? strlen(result) : 0;
    r = (r > 9) ? r + '7' : r + '0';
    result[l] = r;
    result[l + 1] = '\0';

    if (dec < 0 && !(dec / base))
    {
        reverse(result);
        shiftAdd(result, '-');
        return result;
    }

    return convertToDifferentBase(dec / base, base, result);
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

// 10     2     1010
// 25     3     2201
// 123     4     3003
// 100     5     2020
// 1024     8 10000000
//     0    10        0
// -10     2    -1010
// -25     3    -2201
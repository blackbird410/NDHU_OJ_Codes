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
    int remainder, digit, i = 0;
    char r[SIZE]; 

    // Convert the decimal number in the base specified
    while(dec)
    {
        remainder = dec % base;
        r[i] = (remainder > 9) ? remainder + '7' : remainder + '0';
        dec /= base; 

        i++;
    }

    int l = i - 1;
    for(i = 0; i <= l; i++)
    {
        result[i] = r[l - i];
    }

    result[i] = '\0';

    return result;
}

int main()
{
    int n;
    char result[SIZE];

    scanf("%d", &n);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************
function name: replace
description: When mode is 1, replace the first target found in source with the replacement.
             When mode is 2, replace left-most target by replacement until there are no targets in the source.
return value: Return the result after replace.
*******************************************/
#define SIZE 1000

char *replaceTarget(char *source, char *target, char *rep)
{
    // Replaces the first target found and return the postion of the next target to replace
    char *target_pos = strstr(source, target);
    int pos = 0, i = 0;
    char result[SIZE] = "";

    if (!target_pos) return NULL;
    
    strncat(result, source, target_pos - source);
    strcat(result, rep);
    strcat(result, target_pos + strlen(target));
    strcpy(source, result);

    return source;
}

char *replace(char *source, char *target, char *replacement, int mode) 
{
    char *target_pos = strstr(source, target);
    if (!target_pos)
    {
        return source;
    }

    while(target_pos != NULL)
    {
        target_pos = replaceTarget(source, target, replacement);
        if (mode == 1) break;
    }
    return source;
}

int main()
{
    char source[] = "bbccbhaf";
    char target[] = "bc";
    char rep[] = "cb", *result;

    printf("Source: %s\n", source);
    result = replace(source, target, rep, 1);
    printf("Mode 1: %s\n", result);
    result = replace(source, target, rep, 2);
    printf("Mode 2: %s\n", result);

    return 0;  
}
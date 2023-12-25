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

int replaceTarget(char *source, char *target, char *rep, char *result)
{
    // Replaces the first target found and return whether there was a new target created to the left
    
    // Algorithm
    // ----------
    // Parse the source string while looking for the first character of the target
    // If the first character is found, start checking the rest of the characters
    // If all ther characters in target is found, then you can start replacing the target
    // After replacing the target, add the rest of characters of the source string after the target replaced in the result string
    char *p_source = source, *p_target, *p_rep = rep, *p_result = result;
    int target_replaced = 0, pos = 0, i;

    while(*p_source != '\0')
    {
        if (*p_source == *target && !target_replaced)
        {
            p_target = target;
            i = 0;
            // Start checking  for the rest of the characters
            while(*p_target == *(p_source + i))
                p_target++, i++;

            if (*p_target == '\0')
            {
                pos = strlen(result);

                // Replace the target
                while(*p_rep != '\0')
                {
                    *p_result = *p_rep;
                    p_result++, p_rep++;
                } 
                target_replaced = 1;
                p_source += strlen(target);
            }
        }

        *p_result = *p_source;
        p_result++, p_source++;
    }

    // Check for new left-most target
    if (target_replaced && pos)
    {
        i = 0;
        pos--;
        while(result[pos + i] == target[i])
            i++;
        return (target[i] == '\0');
    }

    return 0;
}

char *replace(char *source, char *target, char *replacement, int mode) 
{
    // Decide of the mode 
    // For mode 1:
    // Parse the source string while checking for the target and assigning the characters in the result string
    // When found replace it in the result string by the replacement string
    // Input the rest of the characters after the first target into the result string 

    // For mode 2:
    // Starting from the left, replace the first target in the result string by the replacement 
    // Check after replacing the target if there were not new target created
    // If yes replace the created one 
    // Continue to replace the left most targets in the result string if more are created
    // Input the rest of the characters in the result string if there is any after replacing all targets in the source string
    
    // Return the result string with target replaced
    char *result = malloc((SIZE + strlen(source)) * sizeof(char));
    if (result == NULL)
    {
        return NULL;
    }

    if (mode == 1)
    {
        // Replace the first target found
        replaceTarget(source, target, replacement, result);
    }
    else
    {
        // Replace the first target found and replaces all new left target created in the result string
        int isThereTarget = replaceTarget(source, target, replacement, result);
        while(isThereTarget)
        {
            strcpy(source, result);
            isThereTarget = replaceTarget(source, target, replacement, result);
        }
    }

    return result;
}

int main()
{
    char source[] = "bbccbck", target[] = "bc", rep[] = "c", *result;
    int mode = 1;

    scanf("%d", &mode);
    result = replace(source, target, rep, mode);
    printf("%s\n", result);

    return 0;  
}
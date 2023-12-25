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
        int pos = replaceTarget(source, target, replacement, result);
        while(pos)
        {
            replaceTarget(source, target, replacement, result);
        }
    }

    return result;
}

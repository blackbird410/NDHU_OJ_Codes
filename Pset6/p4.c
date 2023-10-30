#include <stdio.h>
#include <string.h>

// Find the length of the longest substring without repeating characters
// E.g : BnlVFAbnRcbvHZtqgMFDFRaofEsXQHrtecqWDQKJpRRBEGCpTKlCuMfIjSoGcUSwrGahWEslCZpOpUN

#define SIZE 10000

int main()
{
	int length = 0, i = 0, j = 0, k = 0, l = 0, maxLen = 0, end = 0;
	char str[SIZE], sub[SIZE], maxSub[SIZE];

	scanf("%s", str);
	length = strlen(str);

	// Each index is a starting position, and we find the longest string at each index and compare it to the longest
	for(k = 0; k < length; k++)
	{
		// Getting the longest substring starting at k-position
		for(l = 0, end = 0, i = k; i < length; i++)
		{
			// Search the substring for the current character
			for(j = 0; j < l; j++)
			{
				if(str[i] == sub[j])
				{
					end = 1;
					break;
				}
			}

			if (end)
				break;
			sub[l] = str[i];
			l++;
		}
		l = strlen(sub); 
		if (l > maxLen)
		{
			strcpy(maxSub, sub);
			maxLen  = l;
		}
	}
	
	printf("%s\n", maxSub);
	
	return 0;
}

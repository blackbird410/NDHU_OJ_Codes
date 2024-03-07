#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 2000

int main()
{
    char arr[SIZE], c;
    int n = 0, i = 0, l = 0, sum_odd = 0, sum_even = 0;

    while(1)
    {
	i = 0;
	while(1)
	{
		scanf("%c", &c);
		if (c == 10)
		{
			break;
		}
        	arr[i] = c;
		i++;
	}
    	arr[i] = '\0';

        if (arr[0] == '0')
        {
            break;
        }

        l = strlen(arr), sum_odd = 0, sum_even = 0;

        for (i = 0; i < l; i++)
        {
            if (i % 2)
            {
                sum_even += (arr[i] - 48);
            }
            else
            {
                sum_odd += (arr[i] - 48);
            }
        }

        n = sum_even - sum_odd;

        if (n % 11)
        {
            printf("%s is not a multiple of 11.\n", arr);
        }
        else
        {
            printf("%s is a multiple of 11.\n", arr);
        }
    }

    return 0;
}

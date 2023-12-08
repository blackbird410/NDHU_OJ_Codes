#include <stdio.h>

// #define SIZE 100

int main()
{
	init();
	// char s[SIZE] = "Average: 12.33, but the exact 1 result is 12.3333334.";

	char *str = s;
	int sum = 0;

	int number = 0, i, k = 0;

	for (i = 0; *(str + i) != 0; i++)
	{
		if (*(str + i) >= '0' && *(str + i) <= '9')
		{
			number = (number * 10) + (*(str + i) - '0');
			k++;
		}
		else if (number)
		{
			sum += number;
			number = 0;
			k = 0;
		}
	}

	printf("%d", sum + number);

	return 0;
}

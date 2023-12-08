#include <stdio.h>
#include <string.h>

// Converts Arabic numeral to Roman Numeral

#define SIZE 10000
#define ROMAN_SIZE 13

typedef struct Roman 
{
	char symbol;
	int value;
} Roman;

void convert(int n, char *r);

int main()
{
	int n = 0;
	char result[SIZE];

	scanf("%d", &n);
	convert(n, result);
	printf("%s\n", result);
	
	return 0;	
}

void convert(int n, char *result)
{
	int i = 0, j = 0, k = 0, size = 0, r_index = 0;
	int d = 0, q = 0;
	char l[3];
	const char ROMAN_LETTERS[][3] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
	const int ROMAN_VALUES[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

	while(n)
	{
		d = ROMAN_VALUES[r_index];
		strcpy(l, ROMAN_LETTERS[r_index]);

		q = n / d;

		// Is it > 0?
		if (q == 0)
		{
			// Reduce d and l
			r_index++;

		}
		else
		{
			// Assume n > 0 and therefore q >= 1
			// Append the content of l to the result q times
			for (i = 0; i < q; i++)
			{
				for (j = strlen(l), k = 0; k < j; k++)
				{
					result[size] = l[k];
					size++;
				}
			}

			// Reduce n, d and l
			n = n % d;
			r_index++;
		}
	}

	result[size] = '\0';
}

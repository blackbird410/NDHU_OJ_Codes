#include <stdio.h>
#include <string.h>

#define SIZE 10000
#define ROMAN_SIZE 13

// Write a program to convert Arabic numbers to Roman numerals
typedef struct Roman 
{
	char symbol;
	int value;
} Roman;

// void init(Roman *r);
void convert(int n, char *r);

int main()
{
	int n = 0;
	char result[SIZE];

	// Take input
	scanf("%d", &n);

	// Convert the number
	convert(n, result);

	// Display the result
	printf("%s\n", result);
	
	return 0;	
}

// void init(Roman *r)
// {
// 	int i = 0;
// 	const char ROMAN_LETTERS[][3] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
// 	const int ROMAN_VALUES = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

// 	for (i = 0; i < ROMAN_SIZE; i++)
// 	{
// 		r[i].symbol = ROMAN_LETTERS[i];
// 		r[i].symbol = ROMAN_VALUES[i];
// 	}
// }

void convert(int n, char *result)
{
	int i = 0, j = 0, k = 0, size = 0, r_index = 0;
	int d = 0, q = 0;
	char l[3];
	const char ROMAN_LETTERS[][3] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
	const int ROMAN_VALUES[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

	// Roman r_nums[ROMAN_SIZE];

	// Initialize the roman symbol structure
	// init(r_nums);

	while(n)
	{
		// d = r_nums[r_index].value;
		// strcpy(l, &r_nums[r_index]->symbol);

		d = ROMAN_VALUES[r_index];
		strcpy(l, ROMAN_LETTERS[r_index]);

		// Find the quotient
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

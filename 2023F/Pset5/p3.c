#include <stdio.h>

// Given a series of string of characters, display the frequency of each character in the string in ascending order
// If two characters have the same frequency, the higher ascii value comes first
// Input ends with EOF

// For each string of characters:
// Initialize the frequency table
// Update the frequency of every valid character found
// Record and sort the frequencies greater than zero in a record table
// Display the record values, ascii number first and frequency second
// If it is not the end of input, print a blank line

#define ASCII 95

typedef struct record 
{
	int c;
	int f;
} record;

void sort(record *rec, int size);

int main()
{
	record rec[ASCII];
	int freq[ASCII] = {0}, i, j;
	char c = 'a';

	while(c)
	{
		for (i = 0; i < ASCII; i++)
			freq[i] = 0;

		c = 0;
		while (scanf("%c", &c) == 1 && c != '\n' && c != '\r')
		{
			freq[c - ' ']++;
			i++;
		}

		j = 0;
		for (i = 0; i < ASCII; i++)
		{
			if (freq[i])
			{
				rec[j].c = i + ' ';
				rec[j].f = freq[i];
				j++;	
			}
		}

		sort(rec, j);

		for (i = 0; i < j; i++)
			printf("%d %d\n", rec[i].c, rec[i].f);
		
		if (c)
			printf("\n");
	}

	return 0;
}

void swap(record *a, record *b)
{
	a->c += b->c;
	b->c = a->c - b->c;
	a->c -= b->c;

	a->f += b->f;
	b->f = a->f - b->f;
	a->f -= b->f;
}

void sort(record *rec, int size)
{
	int i, swapped = 1;

	while(swapped)
	{
		swapped = 0;
		for (i = 0; i < size - 1; i++)
		{
			if (rec[i].f > rec[i+1].f || (rec[i].f == rec[i+1].f && rec[i].c < rec[i+1].c))
			{
				swap(rec + i, rec + i + 1);
				swapped = 1;
			}
		}
	}
}

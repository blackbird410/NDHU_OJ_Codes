#include <stdio.h>
#include <stdlib.h>

#define ASCII_SIZE 64

void sort(int *freq, int *record, int counter);

int main()
{
	int freq[ASCII_SIZE], record[ASCII_SIZE], i = 0, counter = 0, end = 0;
	char c = 0;

	// Try with an input file
	FILE *file = NULL;
	file = fopen("sample.txt", "r");
	if (file == NULL)
	{
		printf("File could not be opened.\n");
	}

	// Read each line as an input until end of file
	while(!end)
	{
		// Reinitialize the frequency array for new input
		for(i = 0; i < ASCII_SIZE; i++)
		{
			freq[i] = 0;
		}

		// Read each character in the line and update the their frequency
		while(1)
		{
			// scanf("%c", &c);
			c = getc(file);
			// Check for line breaks or new line
			if (c == '\n' || c == '\r')
				break;
	          	// Check for end of file
			if (c < ' ' || c > '^')
			{
				end = 1;
				break;
			}

			// Update the frequencies
			freq[c - ' ']++;
		}

		// Record the different characters in the input to display
		counter = 0;
		for(i = 0; i < ASCII_SIZE; i++)
		{
			if(freq[i])
			{
				record[counter] = i + ' ';
				counter++;
			}
		}

		// Sort the record in ascending order of the frequencies, if two frequencies are the same, the higher ASCII value precede
		sort(freq, record, counter);

		// Output the record with each ASCI value and frequency on separated line, a blank line separate each sets of output
		for(i = 0; i < counter; i++)
		{
			printf("%d %d\n", record[i], freq[record[i] - ' ']);
		}

		// Display a blank line if end of file not yet attained
		if (!end)
			printf("\n");
	}

	return 0;
}

void sort(int *freq, int *record, int counter)
{
	int i = 0, flag = 1, f1 = 0, f2 =0;
	char temp;

	// Bubble sort
	while(flag)
	{
		flag = 0;
		for(i = 0; i < counter - 1; i++)
		{
			f1 = freq[record[i] - ' '];
			f2 = freq[record[i + 1] - ' '];
			if(f1 > f2 || (f1 == f2 && record[i] < record[i+1]))
			{
				temp = record[i];
				record[i] = record[i+1];
				record[i + 1] = temp;
				flag = 1;
			}
		}
	}
}

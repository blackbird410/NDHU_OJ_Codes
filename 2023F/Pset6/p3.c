#include <stdio.h>

// Write a program to capitalize each sentences of an article.
int is_number(char c);
int is_lowercase(char c);
int is_uppercase(char c);
int is_punct(char c);

int main()
{
	int cap = 1;
	char c = 0, prev = 0, next = 0;

	while(1)
	{
		c = 0;
		scanf("%c", &c);
		if (!c || c == EOF)
			break;
		
		// If there was a type of punctuations that end sentences before, set the next letter to uppercase
		if (cap && is_lowercase(c))
		{
			printf("%c", c - ' ');
			cap = 0;
		}
		else if (cap && is_uppercase(c))
		{
			printf("%c", c);
			cap = 0;
		}
		else
		{
			printf("%c", c);
		}

		if (is_punct(c) && !is_number(prev))
			cap = 1;
		else if (is_punct(c) && is_number(prev))
		{
			scanf("%c", &next);
			if(is_number(next))
				cap = 0;
			if(next)
				printf("%c", next);
			c = next;
		}
		prev = c;
	}

	return 0;
}

int is_number(char c)
{
	int v = (c >= '0' && c <= '9');
	return v;
}

int is_lowercase(char c)
{
	int v = (c >= 'a' && c <= 'z');
	return v;
}

int is_uppercase(char c)
{
	int v = (c >= 'A' && c <= 'Z');
	return v;
}

int is_punct(char c)
{
	int v = (c == '.' || c == '?' || c == '!' || c == '\n');
	return v; 
}

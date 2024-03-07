#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1000
#define ASCII '0'

typedef struct DeciVar
{
	char integer[SIZE];
	char decimal[SIZE];
} DeciVar;

void takeInput(DeciVar *a);
void display(DeciVar sum);
void sum(DeciVar a, DeciVar b, DeciVar *s);

int main()
{
	DeciVar v1, v2, s;

	takeInput(&v1);
	takeInput(&v2);
	sum(v1, v2, &s);
	display(s);

	return 0;
}

void sum(DeciVar a, DeciVar b, DeciVar *s)
{
	int holder = 0;
	int l[2] = {strlen(a.decimal), strlen(b.decimal)}, i;
	int l_max = (l[0] > l[1]) ? l[0] : l[1];

	// Compute the sum of decimals
	while(l[0] > l[1])
	{
		s->decimal[l[0] - 1] = a.decimal[l[0] - 1];
		l[0]--;
	}

	while(l[0] < l[1])
	{
		s->decimal[l[1] - 1] = b.decimal[l[1] - 1];
		l[1]--;
	}

	while(l[0] > 0)
	{
		holder += (a.decimal[l[0] - 1] + b.decimal[l[0] - 1] - 2 * ASCII);
		s->decimal[l[0] - 1] = holder % 10 + ASCII;
		holder /= 10;
		l[0]--;
	}
	for (i = l_max - 1; i >= 0; i--)
		if (s->decimal[i] == '0')
			s->decimal[i] = '\0';
		else
			break;

	// Compute the sum of integers
	l[0] = strlen(a.integer);
	l[1] = strlen(b.integer);
	l_max = (l[0] > l[1]) ? l[0] : l[1];
	int pos = l_max;

	while(pos > 0)
	{
		if (l[0] && l[1])
		{
			holder += (a.integer[l[0] - 1] + b.integer[l[1] - 1] - 2 * ASCII);
			s->integer[pos] = holder % 10 + ASCII;
			holder /= 10;
			l[0]--;
			l[1]--;
		}
		else if (l[0])
		{
			holder += a.integer[l[0] - 1] - ASCII;
			s->integer[pos] = holder % 10 + ASCII ;
			holder /= 10;
			l[0]--;
		}
		else
		{
			s->integer[pos] = holder % 10  + b.integer[l[1] - 1] ;
			holder /= 10;
			l[1]--;
		}
		pos--;
	}

	if (holder)
	{
		s->integer[pos] = holder % 10 + ASCII;
		s->integer[l_max+1] = '\0';
	}
	else
	{
		// Shift the array
		for (i = 0; i < l_max; i++)
			s->integer[i] = s->integer[i + 1];
		s->integer[i] = '\0';
	}

}

void display(DeciVar s)
{
	int flag = 0, i = 0;

	while (flag != 2)
	{
		if (!flag)
		{
			if (s.integer[i] == '\0')
			{
				if (!strlen(s.decimal))
					break;
				printf(".");
				flag++;
				i = 0;
				continue;
			}
			else
				printf("%c", s.integer[i]);
		}
		else
		{
			if (s.decimal[i] == '\0')
				flag++;
			else
				printf("%c", s.decimal[i]);
		}

		i++;
	}
	// printf("\n");
}

void takeInput(DeciVar *a)
{
	
	int i = 0, flag = 0, cInt = 0, cDec = 0;
	char c;
	char s[2 * SIZE + 1];

	scanf("%s", s);

	while(s[i] != '\n' && s[i] != '\0')
	{
		c = s[i];
		if (c == '.')
		{
			flag = 1;
			a->integer[cInt] = '\0';
			i++;
			continue;
		}

		if (!flag)
		{
			a->integer[cInt] = c;
			cInt++;
		}
		else
		{
			a->decimal[cDec] = c;
			cDec++;
		}
		i++;
	}
	
	a->decimal[cDec] = '\0';
	
}

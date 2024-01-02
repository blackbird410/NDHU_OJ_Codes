#include <stdio.h>
#include <stdlib.h>

// Write a program to evaluate a function in the format : F(G(F(4), 4))
// With F(x) = 3 * x + 1 and G(x, y) = x * y - 3

// Solution
// ---------
// Create a recursive function that evaluate the expression until there are only digits in the string
// Returns the result as an integer value

// Algorithm
// ---------
// Parse the string to find F or G or a digit;
// If F or G is found, increment the position variable and evaluate the expression found by also applying the suitable function
// Else collect the digit found and return the integer value of it

#define SIZE 50

int isDigit(char c)
{
	return (c >= '0' && c <='9');
}

int isValid(char *exp)
{
	char *p = exp;
	while(*p == 'F' || *p == 'G' || *p == '(' || *p == ')' || *p == ' ' || *p == ',' || isDigit(*p))
		*p++;
	return *p == '\0';
}

int eval(int *i, char *exp)
{
	// Looking for F, G or a digit
	while(exp[*i] != 'F' && exp[*i] != 'G' && !isDigit(exp[*i]))
		*i += 1;
	if (exp[*i] == 'F' || exp[*i] == 'G')
	{
		*i += 1;
		return (exp[*i - 1] == 'F') ? 3 * eval(i, exp) + 1 : eval(i, exp) * eval(i, exp) - 3;  
	}

	int n = 0;
	while(isDigit(exp[*i]))
	{
		n += exp[*i] - '0';
		*i += 1;
	}

	return n;
}

int main()
{
	char exp[SIZE] = "";
	int i = 0;

	gets(exp);
	if (isValid(exp))
		printf("%d\n", eval(&i, exp));
	else
		printf("Invalid expression\n");

	return 0;
}

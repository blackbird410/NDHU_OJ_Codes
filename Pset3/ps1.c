#include <stdio.h>
#include <stdlib.h>


int main()
{
	int n = 0;
	
	// Take the input
	scanf("%d", &n);

	// Check the modulo for 3 => 2, 7 => 5, 11 => 7
	if (n % 3 == 2 && n % 7 == 5 && n % 11 == 7)
	{
		printf("YES");
	}	
	else
	{
		printf("NO");
	}

	return 0;
}

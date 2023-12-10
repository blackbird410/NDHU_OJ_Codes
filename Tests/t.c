#include <stdio.h>

int w(int n, int k, int i);

int main()
{
	int n, k, i = 0;

	while(scanf("%d %d", &n, &k) == 2 && (n && k))
	{
		while(w(n, k, i) != 1 && i < n)
			i++;
		printf("%d\n", i + 1);
	}

	return 0;
}


int w(int n, int k, int i)
{
	if (n == 1)
		return 0;
	else
		return (w(n - 1, k, i) + (k - i)) % n + i;
}

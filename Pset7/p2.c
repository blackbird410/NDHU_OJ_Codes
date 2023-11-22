#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 25
#define STRING_SIZE 20

void initArray(int (*arr)[SIZE]);
void printArray(int (*arr)[SIZE], int n);
void outputArray(int (*arr)[SIZE], int n);
void findPos(int (*arr)[SIZE], int (*pos)[2], int a, int b);
void returnInit(int (*arr)[SIZE], int i, int j);
void moveOnto(int (*arr)[SIZE], int a, int b);
void moveOver(int (*arr)[SIZE], int a, int b);
void pileOnto(int (*arr)[SIZE], int a, int b);
void pileOver(int (*arr)[SIZE], int a, int b); 
int getCommand(char *str, int *a, int *b);
int sameStack(int (*pos)[2]);

int main()
{
	// Create a 2d squred matrix of dimension 25
	// Initialize the first row with the indexes of the boxes and set other places to -1
	// Implement move functions for the boxes
	// Implement a switch for the different moves
	
	int arr[SIZE][SIZE], i = 0, j = 0, n = 10, a = 0, b = 0, c = 0;
	char str[STRING_SIZE];

	scanf("%d", &n);
	initArray(arr);

	while(fgets(str, STRING_SIZE, stdin) != NULL)
	{
		c = getCommand(str, &a, &b);

		switch(c)
		{
			case 0:
				outputArray(arr, n);
				return 0;
			case 1:
				moveOnto(arr, a, b);
				break;
			case 2:
				moveOver(arr, a, b);
				break;
			case 3:
				pileOnto(arr, a, b);
				break;
			case 4:
				pileOver(arr, a, b);
				break;
			default:
				break;
		}
		// printArray(arr, n);
	}

	return 0;
}

void initArray(int (*arr)[SIZE])
{
	int i = 0, j = 0;
	
	// Initialize the first row
	for(i = 0; i < SIZE; i++)
		arr[0][i] = i;

	// Initialize the other matrix positions to -1
	for(i = 1; i < SIZE; i++)
		for(j = 0; j < SIZE; j++)
			arr[i][j] = -1;
}

void printArray(int (*arr)[SIZE], int n)
{
	int i = 0, j = 0;

	for(i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (arr[i][j] >= 0)
				printf(" %d ", arr[i][j]);
			else
				printf("   ");
		}
		printf("\n");
	}
	printf("\n");
}

void outputArray(int (*arr)[SIZE], int n)
{
	int i = 0, j = 0;

	for (i = 0; i < n; i++)
	{
		printf("%d:", i);
		for (j = 0; j < n; j++)
		{
			if (arr[j][i] == -1)
				break;
			else
				printf(" %d", arr[j][i]);
		}
		// if (i < n - 1)
		printf("\n");
	} 
}

void findPos(int (*arr)[SIZE], int (*pos)[2], int a, int b)
{
	int i = 0, j = 0, pos_found[2] = {0};

        for(i = 0; i < SIZE; i++)
        {
                for(j = 0; j < SIZE; j++)
				{
						// Check if both have been found
                        if (pos_found[0] && pos_found[1])
                                break;

						// The first row of the pos array are the coordinates of a and the second are those of b
                        if (arr[i][j] == a)
                        {
                                pos[0][0] = i;
                                pos[0][1] = j;
                                pos_found[0] = 1;
                        }

                        if (arr[i][j] == b)
                        {
                                pos[1][0] = i;
                                pos[1][1] = j;
								pos_found[1] = 1;
                        }
                }
				// Check if both have been found
				if (pos_found[0] && pos_found[1])
						break;
        }
}

void returnInit(int (*arr)[SIZE], int i, int j)
{
	// i: row index
	// j: column index 
	// Returns all blocks in the column i after the element j to their initial position
	
	int k = 0;
	for (k = i+1; k < SIZE; k++)
	{
		if (arr[k][j] >= 0)
		{
			arr[0][arr[k][j]] = arr[k][j];
			arr[k][j] = -1;
		}
		else
			break;
	}
	
}

void moveOnto(int (*arr)[SIZE], int a, int b)
{
	// Find the position of a and b
	// Removes all blocks on top of a and b, and return them to their initial position
	// Stack a on top of b
	
	int pos[2][2] = {0};

	findPos(arr, pos, a, b);

	if (!sameStack(pos))
	{
		returnInit(arr, pos[0][0], pos[0][1]);
		returnInit(arr, pos[1][0], pos[1][1]);

		// Put block a on top of block b
		arr[pos[1][0]+1][pos[1][1]] = a;
		arr[pos[0][0]][pos[0][1]] =  -1;
	}
}

void moveOver(int (*arr)[SIZE], int a, int b)
{
	// Removes all blocks on top of a and put a on top of the stack containing b
	
	int pos[2][2] = {0}, i = 0, j = 0;

	findPos(arr, pos, a, b);

	if (!sameStack(pos))
	{
		returnInit(arr, pos[0][0], pos[0][1]);

		// Put block a on top of the stack containing b
		j = pos[1][1];
		i = pos[1][0] + 1;
		while(arr[i][j] != -1 && i < SIZE)
			i++;
		arr[i][j] = a;
		arr[pos[0][0]][pos[0][1]] = -1;
	}
}

void pileOnto(int (*arr)[SIZE], int a, int b)
{
	// Removes all blocks on top of b and stack the pile starting at a onto b
	
	int pos[2][2] = {0}, i = 0, j = 0, k = 0;
	
	findPos(arr, pos, a, b);

	if (!sameStack(pos))
	{
		returnInit(arr, pos[1][0], pos[1][1]);

		// Stack the pile containing a onto b
		j = pos[0][1];
		k = pos[1][0] + 1;
		for(i = pos[0][0]; arr[i][j] != -1; i++)
		{
			arr[k][pos[1][1]] = arr[i][j];
			arr[i][j] = -1;
			k++;
		}
	}

}
void pileOver(int (*arr)[SIZE], int a, int b)
{
	// Stack the pile starting at a onto of the stack containing b
	
	int pos[2][2] = {0}, i = 0, j = 0, k = 0, i_a, j_a;

	findPos(arr, pos, a, b);

	if (!sameStack(pos))
	{
		j = pos[1][1];
        i = pos[1][0];
		i_a = pos[0][0];
			while(arr[i][j] >= 0 && i < SIZE)
					i++;

		for(k = i; arr[i_a][pos[0][1]] != -1; k++)
		{
			arr[k][j] = arr[i_a][pos[0][1]];
			arr[i_a][pos[0][1]] = -1;
			i_a++;
		}
	}
}

int getCommand(char *str, int *a, int *b)
{
	int i = 0, l = strlen(str);

	// printf("Length: %d\n", l);

	if (str[0] == 'q')
		return 0;

	if(str[6] == ' ')
		*a = str[5] - '0';
	else
        *a = (str[5] - '0') * 10 + (str[6] - '0');
        
	if(str[l - 3] == ' ')
		*b = str[l-2] - '0';
	else
		*b = (str[l - 3] - '0') * 10 + (str[l - 2] - '0');

	if (*a == *b || *a >= SIZE || *b >= SIZE)
		return -1;
	
	if (str[0] == 'm')
	{
		if (str[9] == 'n' || str[9] == 't')
			return 1;
		else
			return 2;
	}

	if (str[0] == 'p')
	{
		if (str[9] == 'n' ||  str[9] == 't')
			return 3;
		else
			return 4;
	}

	return -1;
}

int sameStack(int (*pos)[2])
{
	if (pos[0][1] == pos[1][1])
		return 1;
	else 
		return 0;
}
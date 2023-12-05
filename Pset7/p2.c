#include <stdio.h>
#include <string.h>
#include <math.h>

#define SIZE 25
#define MOVE_ONTO 1
#define MOVE_OVER 2
#define PILE_ONTO 3
#define PILE_OVER 4
#define QUIT -1
#define ROW 0
#define COL 1
#define POS_A 0
#define POS_B 1
#define EMPTY -1

void init(int (*arr)[SIZE], int n);
int getCommand(char *str, int *a, int *b);
void move_onto(int (*arr)[SIZE], int n, int a, int b);
void move_over(int (*arr)[SIZE], int n, int a, int b);
void pile_onto(int (*arr)[SIZE], int n, int a, int b);
void pile_over(int (*arr)[SIZE], int n, int a, int b);
void output(int (*arr)[SIZE], int n);

int main()
{
	int n = 0, a = 0, b = 0, c = 0, arr[SIZE][SIZE];
	char str[SIZE];

	scanf("%d", &n);
	init(arr, n);

	while(fgets(str, SIZE, stdin) != NULL)
	{
		// Find which command was given
		c = getCommand(str, &a, &b);

		switch(c)
		{
			case MOVE_ONTO:
				move_onto(arr, n, a, b);
				break;
			case MOVE_OVER:
				move_over(arr, n, a, b);
				break;
			case PILE_OVER:
				pile_over(arr, n, a, b);
				break;
			case PILE_ONTO:
				pile_onto(arr, n, a, b);
				break;
			case QUIT:
				output(arr, n);
				return 0;
			default:
				break;
		}
	}

	return 0;
}

void init(int (*arr)[SIZE], int n)
{
	// Initialize the 2D matrix for the world
	int i, j;

	for (j = 0; j < n; j++)
		arr[0][j] = j;

	for (i = 1; i < n; i++)
		for (j = 0; j < n; j++)
			arr[i][j] = EMPTY;
}

int getCommand(char *str, int *a, int *b)
{
	// Find which command was given
	int i = 5, l = strlen(str) - 1, e = 0;
	if (str[0] == 'q')
		return QUIT;

	// Find the value of a
	*a = (str[6] == ' ') ? str[5] - '0' : (str[5] - '0') * 10 + str[6] - '0';

	// Find the value of b
	*b = (str[l - 2] == ' ') ? (str[l-1] - '0') : (str[l-2] - '0') * 10 + (str[l-1] - '0');


	// Distinguish the commands
	if (str[0] == 'm')
	{
		if (str[9] == 'n' || str[9] == 't')
			return MOVE_ONTO;
		else
			return MOVE_OVER;
	}
	else if (str[0] == 'p')
	{
		if (str[9] == 'n' || str[9] == 't')
                        return PILE_ONTO;
                else
                        return PILE_OVER;

	}

	return 0;
}

void findPos(int (*arr)[SIZE], int n, int a, int b, int (*pos)[2])
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (arr[i][j] == a)
			{
				pos[POS_A][ROW] = i;
				pos[POS_A][COL] = j;
			}
			else if (arr[i][j] == b)
			{
				pos[POS_B][ROW] = i;
				pos[POS_B][COL] = j;
			}
		}
	}
}

int isValid(int (*arr)[SIZE], int n, int a, int b, int (*pos)[2])
{
	return (a >= 0 && a < n && b >= 0 && b < n && b != a && pos[POS_A][COL] != pos[POS_B][COL]);
}

void returnInit(int (*arr)[SIZE], int n, int row, int col)
{
	// Returns all blocks on top a block x to their initial position
	int i = row + 1;

	while(i < n && arr[i][col] != EMPTY)
	{
		arr[0][arr[i][col]] = arr[i][col];
		arr[i][col] = EMPTY;
		i++;
	}
}

void move_onto(int (*arr)[SIZE], int n, int a, int b)
{
	int pos[2][2];

	// Find the positon of a and b inside the matrix
	findPos(arr, n, a, b, pos);

	// Check if the command is valid
	if (isValid(arr, n, a, b, pos))
	{
		// Remove all blocks on top of a and on top of b
		returnInit(arr, n, pos[POS_A][ROW], pos[POS_A][COL]);
		returnInit(arr, n, pos[POS_B][ROW], pos[POS_B][COL]);

		// Move a onto b
		arr[pos[POS_B][ROW] + 1][pos[POS_B][COL]] = arr[pos[POS_A][ROW]][pos[POS_A][COL]];
		arr[pos[POS_A][ROW]][pos[POS_A][COL]] = EMPTY;
	}
}

void move_over(int (*arr)[SIZE], int n, int a, int b)
{
	int pos[2][2], i = 0;

	// Find the positon of a and b inside the matrix
	findPos(arr, n, a, b, pos);

	// Check if the command is valid
	if (isValid(arr, n, a, b, pos))
	{
		// Remove all blocks on top of a
		returnInit(arr, n, pos[POS_A][ROW], pos[POS_A][COL]);

		// Find the next empty spot in the stack
		i = pos[POS_B][ROW] + 1;
		while(arr[i][pos[POS_B][COL]] != EMPTY)
			i++;

		// Move a onto b
		arr[i][pos[POS_B][COL]] = arr[pos[POS_A][ROW]][pos[POS_A][COL]];
		arr[pos[POS_A][ROW]][pos[POS_A][COL]] = EMPTY;
	}
}

void pile_onto(int (*arr)[SIZE], int n, int a, int b)
{
	int pos[2][2], i = 0, j = 0;

	// Find the positon of a and b inside the matrix
	findPos(arr, n, a, b, pos);

	// Check if the command is valid
	if (isValid(arr, n, a, b, pos))
	{
		// Remove all blocks on top of b
		returnInit(arr, n, pos[POS_B][ROW], pos[POS_B][COL]);

		// Pile a and all the blocks on top of a onto b
		i = pos[POS_A][ROW];
		j = pos[POS_B][ROW] + 1;
		while(i < n && arr[i][pos[POS_A][COL]] != EMPTY)
		{
			arr[j][pos[POS_B][COL]] = arr[i][pos[POS_A][COL]];
			arr[i][pos[POS_A][COL]] = EMPTY;
			i++;
			j++;
		}
	}
}

void pile_over(int (*arr)[SIZE], int n, int a, int b)
{
	int pos[2][2], i = 0, j = 0;

	// Find the positon of a and b inside the matrix
	findPos(arr, n, a, b, pos);

	// Check if the command is valid
	if (isValid(arr, n, a, b, pos))
	{

		i = pos[POS_A][ROW];

		// Find the next empty spot over b
		j = pos[POS_B][ROW] + 1;
		while(arr[j][pos[POS_B][COL]] != EMPTY)
			j++;

		// Pile a and all the blocks on top of a over b
		while(i < n && arr[i][pos[POS_A][COL]] != -1)
		{
			arr[j][pos[POS_B][COL]] = arr[i][pos[POS_A][COL]];
			arr[i][pos[POS_A][COL]] = EMPTY;
			i++;
			j++;
		}
	}
}

void output(int (*arr)[SIZE], int n)
{
	int i, j;

	// Display the array in 2 dimension
	// for (i = n - 1; i >= 0; i--)
	// {
	// 	for (j = 0; j < n; j++)
	// 	{
	// 		if (arr[i][j] == EMPTY)
	// 			printf("* ");
	// 		else
	// 			printf("%d ", arr[i][j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");

	for (i = 0; i < n; i++)
	{
		printf("%d:", i);
		for (j = 0; j < n; j++)
		{
			if (arr[j][i] != EMPTY)
				printf(" %d", arr[j][i]);
			else
				break;
		}
		printf("\n");
	}
}

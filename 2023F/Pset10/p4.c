#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define LIFE 1
#define DEATH 0

typedef struct Dim
{
	int row;
	int col;
} Dim;

void takeInput(int (*arr)[SIZE], Dim *d, int *n);
void display(int (*arr)[SIZE], Dim d);
void playGame(int (*arr)[SIZE], Dim d, int n);

int main()
{
	int arr[SIZE][SIZE], n, row, col;
	Dim d;

	takeInput(arr, &d, &n);
	playGame(arr, d, n);
	display(arr, d);
}

void emptyBuffer()
{
	while(getchar() != '\n');
}

void takeInput(int (*arr)[SIZE], Dim *d, int *n)
{
	char line[SIZE];
	int i = 0, j = 0;

	scanf("%d\n", n);

	while (fgets(line, SIZE, stdin) !=  NULL)
	{
		j = 0; 
		while (line[j] != '\0' && line[j] != '\n')
		{
			arr[i][j] = line[j] - '0';
			j++;
		}
		i = (j) ? i + 1: i;		
	}

	d->row = i;
	d->col = j;
}

void display(int (*arr)[SIZE], Dim d)
{
	int i, j;
	
	for (i = 0; i < d.row; i++)
	{
		for(j = 0; j < d.col; j++)
			printf("%d", arr[i][j]);
		printf("\n");
	}
}

void copy(int (*game)[SIZE], int (*cpy)[SIZE], Dim d)
{
	int i, j;
	for (i = 0; i < d.row; i++)
		for (j = 0; j < d.col; j++)
			cpy[i][j] = game[i][j];
}

int isSafe(int row, int col, Dim d)
{
	return (row >= 0 && col >= 0 && row < d.row && col < d.col);
}

int lifeOrDeath(int (*cpy)[SIZE], Dim d, int row, int col)
{
	int count = 0;

	// Count alive neighbors
	int i, j;
	for (i = -1; i < 2; i++)
	{
		for (j = -1; j < 2; j++)
		{
			if ((i || j) && isSafe(row + i, col + j, d) && cpy[row + i][col + j])
				count++;
		}
	}

	switch(count)
	{
		case 0:
		case 1:
			return DEATH;
		case 2:
			return cpy[row][col];
		case 3:
			return LIFE;
		default:
			return DEATH;
	}
}

void animate(int (*arr)[SIZE], Dim d)
{
	int i, j;
	
	for (i = 0; i < d.row; i++)
	{
		for(j = 0; j < d.col; j++)
		{
			if (arr[i][j] == LIFE)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
	printf("\n");
}

void playGame(int (*game)[SIZE], Dim d, int n)
{
	int i, j, cpy[SIZE][SIZE];

	while (n--)
	{
		copy(game, cpy, d);
		// animate(game, d);
		for (i = 0; i < d.row; i++)
			for(j = 0; j < d.col; j++)
				game[i][j] = lifeOrDeath(cpy, d, i, j);
	}
}
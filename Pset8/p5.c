#include <stdio.h>
#include <stdlib.h>

#define SIZE 19
#define SIZE_BOARD SIZE*SIZE
#define WHITE 0
#define BLACK 1
#define NO_WINNER -1
#define NO_STONE -1
#define LOWER_BOUND 4
#define UPPER_BOUND 14
#define SE 1
#define SW 2
#define NE 3
#define NW 4

void inputGame(int (*game)[SIZE]);
int getWinner(int (*game)[SIZE]);

int main()
{
	int game[SIZE][SIZE], winner;

	inputGame(game);
	winner = getWinner(game);

	switch(winner)
	{
		case WHITE:
			printf("White");
			break;
		case BLACK:
			printf("Black");
			break;
		default:
			printf("No winner");
			break;
	}

	return 0;
}

void inputGame(int (*game)[SIZE])
{
	int i = 0, j = 0, count = 0;;
	char str[SIZE + 1];

	while(i < SIZE)
	{
		fgets(str, SIZE + 1, stdin);
		for(j = 0; j < SIZE; j++)
		{
			switch(str[j])
			{
				case 'O':
					game[i][j] = WHITE;
					break;
				case 'X':
					game[i][j] = BLACK;
					break;
				case '_':
					game[i][j] = NO_STONE;
					break;
				default:
					break;
			}
			
		}
		while ((getchar()) != '\n');
		i++;
	}
}


int checkHorizontal(int (*game)[SIZE])
{
	int i, j, count, previous;

	for (i = 0; i < SIZE; i++)
	{
		previous = game[i][0];
		count = (previous == BLACK || previous == WHITE);
		for (j = 1; j < SIZE; j++)
		{
			if (game[i][j] == WHITE || game[i][j] == BLACK)
			{
				if (previous == game[i][j])
					count++;
				else if (game[i][j] != NO_STONE)
					count = 1;
				else 
					count = 0;

				if (count == 5)
					return previous;
			}
			previous = game[i][j];
		}
	}

	return NO_WINNER;
}

int checkVertical(int (*game)[SIZE])
{
	int i, j, count, previous;

	for (i = 0; i < SIZE; i++)
	{
		previous = game[0][i];
		count = (previous == BLACK || previous == WHITE);
		for (j = 1; j < SIZE; j++)
		{
			if (game[j][i] == WHITE || game[j][i] == BLACK)
			{
				if (previous == game[j][i])
					count++;
				else if (game[j][i] != NO_STONE)
					count = 1;
				else
					count = 0;

				if (count == 5)
					return previous;
			}
			previous = game[j][i];
		}
	}

	return NO_WINNER;
}



int countPieces(int (*game)[SIZE], int i, int j, int d)
{
	int count, k;

	switch(d)
	{
		case SE:
		count = 0;
			for (k = 0; k <= LOWER_BOUND; k++)
			{
				if (game[i][j] == NO_STONE || game[i + k][j + k] != game[i][j])
					break;
				count = (game[i + k][j + k] == game[i][j]) ? count + 1: count;
			}
			break;
		case SW:
			count = 0;
			for (k = 0; k <= LOWER_BOUND; k++)
			{
				if (game[i][j] == NO_STONE || game[i + k][j - k] != game[i][j])
					break;
				count = (game[i + k][j - k] == game[i][j]) ? count + 1: count;
			}
			break;
		default:
			count = NO_WINNER;
			break;
	}

	return count;
}

int checkDiagonal(int (*game)[SIZE])
{
	int i, j, k, count;
	
	// Counting in all directions
	for (i = 0; i <= UPPER_BOUND; i++)
	{ 
		for (j = 0; j <= UPPER_BOUND; j++)
		{
			count = countPieces(game, i, j, SE);
			
			if (count == 5)
				return game[i][j];
		}
	}

	for (i = 0; i <= UPPER_BOUND; i++)
	{
		for (j = LOWER_BOUND; j < SIZE; j++)
		{
			count = countPieces(game, i, j, SW);
			
			if (count == 5)
				return game[i][j];
		}
	}

	return NO_WINNER;
}

int getWinner(int (*game)[SIZE])
{
	int winner;

	winner = checkHorizontal(game);
	if (winner != NO_WINNER)
		return winner;

	winner = checkVertical(game);
	if (winner != NO_WINNER)
		return winner;

	winner = checkDiagonal(game);
	if (winner != NO_WINNER)
		return winner;

	return NO_WINNER;
}

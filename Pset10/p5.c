#include <stdio.h>
#include <stdlib.h>

#define SIZE 9
#define BLACK 'X'
#define WHITE 'O'
#define EMPTY '.'

typedef struct Game
{
	char board[SIZE][SIZE];
	int black;
	int white;
} Game;

void takeInput(Game *game);
void countPoints(Game *game);

int main()
{
	Game *game = malloc(sizeof(Game));
	if (game == NULL)
		return 1;

	int n = 0;
	scanf("%d\n", &n);
	while(n--)
	{
		takeInput(game);
		countPoints(game);
		printf("Black %d White %d\n", game->black, game->white);
	}

	free(game);

	return 0;
}

void emptyBuffer()
{
	while (getchar() != '\n');
}

void takeInput(Game *game)
{
	int i, j;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
			scanf("%c", &game->board[i][j]);
		emptyBuffer();		
	}
	game->black = 0;
	game->white = 0;
}

int isBound(int row, int col)
{
	return (row >= 0 && row < SIZE && col >= 0 && col < SIZE);
}

void updateCounter(Game *game, char player, int count)
{
	if (player == BLACK)
	{
		game->black += count;
	}
	else
	{
		game->white += count;
	}
}

int isFree(Game *game, int row, int col)
{
	int w = 0, b = 0;

	if (isBound(row, col - 1) && game->board[row][col - 1] != EMPTY)
	{
		w = (game->board[row][col - 1] == WHITE) ? w + 1 : w;
		b = (game->board[row][col - 1] == BLACK) ? b + 1 : b;
	}

	if (isBound(row - 1, col) && game->board[row - 1][col] != EMPTY)
	{
		w = (game->board[row - 1][col] == WHITE) ? w + 1 : w;
		b = (game->board[row - 1][col] == BLACK) ? b + 1 : b;
	}
	
	if (isBound(row, col + 1) && game->board[row][col + 1] != EMPTY)
	{
		w = (game->board[row][col + 1] == WHITE) ? w + 1 : w;
		b = (game->board[row][col + 1] == BLACK) ? b + 1 : b;
	}

	if (isBound(row + 1, col) && game->board[row + 1][col] != EMPTY)
	{
		w = (game->board[row + 1][col] == WHITE) ? w + 1 : w;
		b = (game->board[row + 1][col] == BLACK) ? b + 1 : b;
	}

	if(w && b && w + b == 4)
		return 1;
	return 0;
}


void countPoints(Game *game)
{
	int count = 0, i, j;
	char piece;

	for (i = 0; i < SIZE; i++)
	{
		piece = game->board[i][j];
		for (j = 0; j < SIZE; j++)
		{
			if (game->board[i][j] != piece)
			{
				if (piece == EMPTY)
				{
					piece = game->board[i][j];
				}
				else if (game->board[i][j] != EMPTY)
				{
					updateCounter(game, piece, count);
					piece = game->board[i][j];
					count = 0;
				}
			}
			count = (game->board[i][j] != EMPTY || game->board[i][j] == EMPTY && !isFree(game, i, j)) ? count + 1: count;
		}
		updateCounter(game, piece, count);
		count = 0;
	}
}


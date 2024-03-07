#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 9
#define BLACK 'X'
#define WHITE 'O'
#define EMPTY '.'

typedef struct Game
{
	char board[SIZE][SIZE];
	int black;
	int white;
	int count;
	int isBlack;
	int isWhite;
} Game;

void takeInput(Game *game);
void countPoints(Game *game);

int main()
{
	Game game;

	int cases;
	scanf("%d\n", &cases);
	while(cases--)
	{
		takeInput(&game);
		countPoints(&game);
		printf("Black %d White %d\n", game.black, game.white);
	}

	return 0;
}

void takeInput(Game *game)
{
	int i, j;

	game->black = 0;
	game->white = 0;

	for (i = 0; i < SIZE; i++)
	{
		gets(game->board[i]);
		for (j = 0; j < SIZE; j++)
		{
			game->black = (game->board[i][j] == 'X') ? game->black + 1: game->black;
			game->white = (game->board[i][j] == 'O') ? game->white + 1: game->white;
		}	
	}
}

int DFS(Game *game, int row, int col)
{
	if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) 
		return 1;

	if (game->board[row][col] == EMPTY)
	{
		game->board[row][col] = '*';
		game->count += 1;
	}
	else
	{
		if (game->board[row][col] == BLACK)
			game->isBlack = 1;
		else if (game->board[row][col] == WHITE) 
			game->isWhite = 1;
		return 0;
	}

	// Find the closest pieces
	DFS(game, row - 1, col);
	DFS(game, row + 1, col);
	DFS(game, row, col - 1);
	DFS(game, row, col + 1);
}

void countPoints(Game *game)
{
	int i, j;
	char piece;

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			if (game->board[i][j] == EMPTY)
			{
				game->isBlack = 0;
				game->isWhite = 0;
				game->count = 0;
				DFS(game, i, j);

				if (game->isBlack && game->isWhite) 
					continue;
				if (game->isBlack) 
					game->black += game->count;
				else if (game->isWhite) 
					game->white += game->count;
			}
		}
	}
}


#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define PATH_FOUND 1
#define SPACE 0
#define WALL 1
#define STEP 1
#define DOWN 2
#define RIGHT 6
#define LEFT 4
#define UP 8
#define DEAD_END 5
#define MARKED -1

typedef struct Coordinates
{
	int x;
	int y;
} Coord;

typedef struct Maze 
{
	int board[SIZE][SIZE];
	int size;
	Coord route[SIZE * SIZE];
	int pos;

} Maze;

void inputMaze(Maze *maze);
int findPath(Maze *maze);
void display(Maze *maze);
int canExit(Maze *maze);

int main()
{
	Maze *maze =  NULL;
	maze = malloc(sizeof(Maze));
	if (maze == NULL)
	{
		printf("Could not allocate memory.\n");
		return 1;
	}

	int answer; 

	while(scanf("%d", &maze->size) == 1 && maze->size)
	{
		inputMaze(maze);
		if (!canExit(maze))
		{
			printf("No\n");
			continue;
		}

		answer = findPath(maze);
		switch(answer)
		{
			case PATH_FOUND:
				printf("Yes\n");
				break;
			default:
				printf("No\n");
				break;
		}
	}

	free(maze);
	return 0;
}

void inputMaze(Maze *maze)
{
	int i, j;

	for (i = 0; i < maze->size; i++)
	{
		for (j = 0; j < maze->size; j++)
			scanf("%d", &maze->board[i][j]);
		maze->route[i].x = 0;
		maze->route[i].y = 0;
	}
	maze->pos = 0;
}

int isBound(int row, int col, int size)
{
	return (row >= 0 && row < size && col >= 0 && col < size);
}

int isSafe(Maze *maze, int row, int col)
{
	return (isBound(row, col, maze->size) && maze->board[row][col] == SPACE);
}

int walk(Maze *maze)
{
	int row = maze->route[maze->pos].y, col = maze->route[maze->pos].x;

	if (isSafe(maze, row + STEP, col) && maze->board[row + STEP][col] == SPACE)
		return DOWN;
	else if (isSafe(maze, row, col + STEP) && maze->board[row][col + STEP] == SPACE)
		return RIGHT;
	else if (isSafe(maze, row, col - STEP) && maze->board[row][col - STEP] == SPACE)
		return LEFT;
	else if (isSafe(maze, row - STEP, col) && maze->board[row - STEP][col] == SPACE)
		return UP;
	else 
		return DEAD_END;
}

void updatePos(Maze *maze, int row, int col)
{
	maze->pos++;
	maze->route[maze->pos].x = col;
	maze->route[maze->pos].y = row;
}

int arrived(Maze *maze)
{
	return (maze->route[maze->pos].x == maze->size - 1 && maze->route[maze->pos].y == maze->size - 1);
}

int backtrack(Maze *maze)
{
	if (maze->pos == 0)
		return DEAD_END;
	
	maze->pos--;
	display(maze);
	return !PATH_FOUND;
}

void display(Maze *maze)
{
	int i, j;

	for (i =0; i < maze->size; i++)
	{
		for (j = 0; j < maze->size; j++)
		{
			if (i == maze->route[maze->pos].y && j == maze->route[maze->pos].x)
				printf(" X ");
			else if(maze->board[i][j] == MARKED)
				printf(" * ");
			else 
				printf(" %d ", maze->board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int findPath(Maze *maze)
{
	int direction = walk(maze), new_path;
	int row = maze->route[maze->pos].y, col = maze->route[maze->pos].x;

	display(maze);
	if (arrived(maze))
		return PATH_FOUND;
	maze->board[row][col] = MARKED;

	switch(direction)
	{
		case DOWN:
			updatePos(maze, row + STEP, col);
			return findPath(maze);
		case RIGHT:
			updatePos(maze, row, col + STEP);
			return findPath(maze);
		case LEFT:
			updatePos(maze, row, col - STEP);
			return findPath(maze);
		case UP:
			updatePos(maze, row - STEP, col);
			return findPath(maze);
		case DEAD_END:
			if (arrived(maze))
				return PATH_FOUND;

			new_path = backtrack(maze);

			if (new_path == DEAD_END)
				return !PATH_FOUND;
			return findPath(maze);
	}
}

int canExit(Maze *maze)
{
	return (maze->board[maze->size - 1][maze->size - 1] == SPACE);
}

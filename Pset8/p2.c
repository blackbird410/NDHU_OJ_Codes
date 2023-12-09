#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define YES 1
#define NO 0
#define DOWN 2
#define RIGHT 6
#define LEFT 4
#define UP 8
#define DEAD_END 5
#define WALL 1
#define SPACE 0
#define MARKED -1
#define ERROR 1
#define OPEN 1
#define CLOSED 0
#define PATH_FOUND 1
#define PATH_NOT_FOUND 0

typedef struct Maze
{
	int board[SIZE][SIZE];
	int p_x;
	int p_y;
	int size;
} Maze;

typedef struct Paths
{
	int down;
	int right;
	int left;
	int up;
	int count;
} Paths;

void initPaths(Paths *paths)
{
	paths->down = CLOSED;
	paths->right = CLOSED;
	paths->left = CLOSED;
	paths->up = CLOSED;
	paths->count = 0;
}

void inputMaze(Maze *maze);
int solveMaze(Maze *maze);

int main()
{
	int answer;
	Maze maze;

	while(scanf("%d", &maze.size) == 1 && maze.size)
	{
		inputMaze(&maze);
		answer = solveMaze(&maze);
		switch(answer)
		{
			case YES:
				printf("Yes\n");
				break;
			case NO:
				printf("No\n");
				break;
			default:
				break;
		}
	}

	return 0;
}

void inputMaze(Maze *maze)
{
	int i, j;
	maze->p_x = 0;
	maze->p_y = 0;

	for (i = 0; i < maze->size; i++)
		for (j = 0; j < maze->size; j++)
			scanf("%d", &maze->board[i][j]);
}

void display(Maze *maze)
{
	int i, j;
	for (i = 0; i < maze->size; i++)
	{
		for (j = 0; j < maze->size; j++)
		{
			if (i == maze->p_y && j == maze->p_x)
				printf(" X ");
			else if (maze->board[i][j] == -1)
				printf(" * ");
			else 
				printf(" %d ", maze->board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int isBound(int row, int col, int n)
{
	return  (row >= 0 && row < n && col >= 0 && col < n);
}

int isSafe(Maze *maze, int row, int col)
{
	return (isBound(row, col, maze->size) && maze->board[row][col] == SPACE);
}

int walk(Maze *maze)
{
	int row = maze->p_y, col = maze->p_x;

	if (isSafe(maze, row + 1, col))
		return DOWN;
	else if (isSafe(maze, row, col + 1))
		return RIGHT;
	else if (isSafe(maze, row, col - 1))
		return LEFT;
	else if (isSafe(maze, row - 1, col))
		return UP;
	else 
		return DEAD_END;
}

Paths *findPath(Maze *maze)
{
	Paths *paths =  NULL;
	paths = malloc(sizeof(Paths));
	if (paths == NULL)
	{
		printf("Could not allocate memory.\n");
		exit(ERROR); 
	}

	initPaths(paths);
	int row = maze->p_y, col = maze->p_x;

	if (isBound(row + 1, col, maze->size) && maze->board[row + 1][col] == -1)
	{
		paths->down = OPEN;
		paths->count++; 
	}
	if (isBound(row, col + 1, maze->size) && maze->board[row][col + 1] == -1)
	{
		paths->right = OPEN;
		paths->count++;
	}
	if (isBound(row, col - 1, maze->size) && maze->board[row][col - 1] == -1)
	{
		paths->left = OPEN;
		paths->count++;
	}
	if (isBound(row - 1, col, maze->size) && maze->board[row - 1][col] == -1)
	{
		paths->up = OPEN;
		paths->count++;
	}

	return paths;
}

int backtrack(Maze *maze)
{
	// Find an open path while sealing invalid paths
	Paths *paths = findPath(maze);

	switch(paths->count)
	{
		case 1:
			maze->board[maze->p_y][maze->p_x] = 1;
			if (paths->down)
				maze->p_y++;
			else if (paths->right)
				maze->p_x++;
			else if (paths->left)
				maze->p_x--;
			else
				maze->p_y--;
			free(paths);
			return PATH_FOUND;
		case 2:
		case 3:
		case 4:
		default:
			free(paths);
			return PATH_NOT_FOUND;
	}
	free(paths);
}

int solveMaze(Maze *maze)
{
	int d = walk(maze), row = maze->p_y, col = maze->p_x, new_path;
	display(maze);

	maze->board[row][col] = (d != DEAD_END) ? MARKED: maze->board[row][col];
	switch(d)
	{
		case DOWN:
			maze->p_y += 1;
			return solveMaze(maze);
		case RIGHT:
			maze->p_x += 1;
			return solveMaze(maze);
		case LEFT:
			maze->p_x -= 1;
			return solveMaze(maze);
		case UP:
			maze->p_y -= 1;
			return solveMaze(maze);
		case DEAD_END:
			if (row == maze->size - 1 && col == maze->size - 1)
				return YES;

			new_path = backtrack(maze);
			display(maze);
			if (!new_path)
				return NO;
			return solveMaze(maze);
	}

	return NO;
}

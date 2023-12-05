#include <stdio.h>

#define SIZE 1000
#define X 0
#define Y 1
#define COORD 2
#define DOWN 2
#define RIGHT 6
#define LEFT 4
#define UP 8
#define DEAD_END 5
#define PATH_FOUND 1
#define PATH_NOT_FOUND 0

void createMaze(int (*maze)[SIZE], int n);
void output(int (*maze)[SIZE], int n);
int solveMaze(int (*arr)[SIZE], int n, int *pos);

int main()
{
	int maze[SIZE][SIZE], pos[COORD] = {0}, n = 0, result;

	while(scanf("%d", &n) == 1 && n > 0)
	{
		createMaze(maze, n);
		output(maze, n);
		result = solveMaze(maze, n, pos);
		if (result)
			printf("Yes\n");
		else
			printf("No\n");
	}
}

int isWithinBoundary(int n, int col, int row)
{
	return (row >= 0 && row < n && col >= 0 && col < n);
}

int isSafe(int (*maze)[SIZE], int n, int col, int row)
{
	return (isWithinBoundary(n, col, row) && maze[row][col] == 0);
}

int walk(int (*maze)[SIZE], int n, int *pos)
{
	// Main direction to take are in this order: DOWN, RIGHT, LEFT, UP

	if (isSafe(maze, n, pos[X], pos[Y] + 1))
		return DOWN;
	else if (isSafe(maze, n, pos[X] + 1, pos[Y]))
		return RIGHT;
	else if (isSafe(maze, n, pos[X] - 1, pos[Y]))
		return LEFT;
	else if (isSafe(maze, n, pos[X], pos[Y] - 1))
		return UP;
	else
		return DEAD_END;
}

int backtrack(int (*maze)[SIZE], int n, int *pos)
{
	// Return at the previous crossroad and blocking the paths that have dead ends if no new path is found
	int col = pos[X], row = pos[Y];

	// We will ommit the case of checking if there is a path down because we cannot be backtracking and find another path leading DOWN
	// Because our primary direction will always be DOWN

	if (isWithinBoundary(n, col + 1, row))
	{
		// Found a path toward the left
		if (isSafe(maze, n, col + 1, row))
		{
			// Mark the crossroad as open to come back
			maze[row][col] = 0;
			return PATH_FOUND;
		}
		
		// TODO: Distinguish the paths to be closed when backtracking and those to be left open
		// if (maze[row][col + 1] == -1 )
	}	
	else if (isWithinBoundary(n, col - 1, row) && isSafe(maze, n, col - 1, row))
	{
		// Found a path toward the right

		maze[row][col] = 0;
		return PATH_FOUND;
	}
	else if (isWithinBoundary(n, col, row - 1), && isSafe(maze, n, col, row - 1))
	{
		// Found a path UP

		maze[row][col] = 0;
		return PATH_FOUND;
	}

	return PATH_NOT_FOUND;
}

int solveMaze(int (*maze)[SIZE], int n, int *pos)
{
	// Walk to the lower right bottom until it there are no path available
	int col = pos[X], row = pos[Y], direction, done;

	if (pos[X] = n - 1 && pos[Y] == n - 1)
		return PATH_FOUND;
	else
	{
		direction = walk(maze, n, pos);

		switch(direction)
		{
			case DOWN:
				maze[row][col] -= 1;
				*pos[Y] += 1;
				break;
			case RIGHT:
				maze[row][col] -= 1;
				*pos[X] += 1;
				break;
			case LEFT:
				maze[row][col] -= 1;
				*pos[X] -= 1;
				break;
			case UP:
				maze[row][col] -= 1;
				*pos[Y] -= 1;
				break;
			case DEAD_END:
				done = PATH_NOT_FOUND;
				while(!done)
				{
					done = backtrack(maze, n, pos);
				}

				direction = walk(maze, n, pos);
				if (direction == DEAD_END)
					return PATH_NOT_FOUND;
				else
					return solveMaze(maze, n, pos);
		}
	}

}

void createMaze(int (*maze)[SIZE], int n)
{
	// Take the maze input
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &maze[i][j]);
}

void output(int (*arr)[SIZE], int n)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
			printf(" %d ", arr[i][j]);
		printf("\n");
	}
}

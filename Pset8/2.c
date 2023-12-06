#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
#define SEAL 1

typedef struct Position
{
	int x;
	int y;
} Position;

void initPos(Position *pos)
{
	pos->x = 0;
	pos->y = 0;
}

void createMaze(int (*maze)[SIZE], int n);
void output(int (*arr)[SIZE], int n, Position *pos);
int solveMaze(int (*maze)[SIZE], int n, Position *pos);
// void test();

int main()
{
	int maze[SIZE][SIZE], n = 0, result;
	Position pos;

	while(scanf("%d", &n) == 1 && n > 0)
	{
		createMaze(maze, n);
		initPos(&pos);
		result = solveMaze(maze, n, &pos);
		if (result)
			printf("Yes\n");
		else
			printf("No\n");
	}

	// test();
}

int isWithinBoundary(int n, int col, int row)
{
	return (row >= 0 && row < n && col >= 0 && col < n);
}

int isSafe(int (*maze)[SIZE], int n, int col, int row)
{
	return (isWithinBoundary(n, col, row) && maze[row][col] == 0);
}

int walk(int (*maze)[SIZE], int n, Position *pos)
{
	// Main direction to take are in this order: DOWN, RIGHT, LEFT, UP
	int col = pos->x, row = pos->y;

	if (isSafe(maze, n, col, row + 1))
		return DOWN;
	else if (isSafe(maze, n, col + 1, row))
		return RIGHT;
	else if (isSafe(maze, n, col - 1, row))
		return LEFT;
	else if (isSafe(maze, n, col, row - 1))
		return UP;
	else
		return DEAD_END;
}

int moreThanOne(int (*maze)[SIZE], int n, Position *pos)
{
	// Look around and see how much path you can take at a crossroad
	int paths = 0, col = pos->x, row = pos->y;
	int p[11] = {0};

	if (isWithinBoundary(n, col, row + 1) && maze[row + 1][col] == 0 || maze[row + 1][col] == -1)
	{	
		paths++;
		p[DOWN] = 1;
	}
	if (isWithinBoundary(n, col + 1, row) && maze[row][col + 1] == 0 || maze[row][col + 1] == -1)
	{
		paths++;
		p[RIGHT] = 1;
	}
	if (isWithinBoundary(n, col - 1, row) && maze[row][col - 1] == 0 || maze[row][col - 1] == -1)
	{
		paths++;
		p[LEFT] = 1;
	}
	if (isWithinBoundary(n, col, row - 1) && maze[row - 1][col] == 0 || maze[row - 1][col] == -1)
	{
		paths++;
		p[UP] = 1;
	}

	switch(paths)
	{
		case 1:
			return SEAL;
		case 2:
			if (p[UP] && p[RIGHT] && maze[row - 1][col + 1] == 1|| p[UP] && p[LEFT] && maze[row - 1][col - 1] == 1
			|| p[DOWN] && p[RIGHT] && maze[row + 1][col + 1] == 1|| p[DOWN] && p[LEFT] && maze[row + 1][col - 1] == 1)
				return !SEAL;
			else if (p[LEFT] && p[RIGHT])
			{
				if (isWithinBoundary(n, col, row + 1) && (maze[row + 1][col] == 1 || maze[row + 1][col - 1] == 1 || maze[row + 1][col + 1] == 1) 
				&& isWithinBoundary(n, col, row - 1) && (maze[row - 1][col] == 1 || maze[row - 1][col - 1] == 1 || maze[row - 1][col + 1] == 1))
					return !SEAL;
				else
					return SEAL;
			}
			else
				return SEAL;
		case 3:
			if (p[UP] && p[RIGHT] && p[DOWN] && maze[row + 1][col + 1])
			{
				return !SEAL;
			}
			else if (p[UP] && p[RIGHT] && p[LEFT])
			{
				if (isWithinBoundary(n, col, row + 1) && (maze[row + 1][col - 1] == 1 || maze[row + 1][col + 1] == 1 
				|| maze[row - 1][col - 1] == 1 || maze[row - 1][col + 1] == 1))
					return !SEAL;
				else
					return SEAL;
			}
			else 
				return SEAL;
		case 4:
			if ((maze[row + 1][col - 1] == 1 || maze[row + 1][col + 1] == 1 
				|| maze[row - 1][col - 1] == 1 || maze[row - 1][col + 1] == 1))
				return !SEAL;
			else
				return SEAL;
		default:
			return SEAL;
	}
}

void crossPath(int (*maze)[SIZE], int n, Position *pos)
{
	int col = pos->x, row = pos->y;

	// If there are more than one path to take, leave the crossroad open
    if (!moreThanOne(maze, n, pos))
		maze[row][col] = -1;
	else
		maze[row][col] = 1;
}

int backtrack(int (*maze)[SIZE], int n, Position *pos)
{
	// Return at the previous crossroad and blocking the paths that have dead ends if no new path is found
	int col = pos->x, row = pos->y;

	// We will ommit the case of checking if there is a path down because we cannot be backtracking and find another path leading DOWN
	// Because our primary direction will always be DOWN

	crossPath(maze, n, pos);
	if (isWithinBoundary(n, col + 1, row))
	{
		// Found a path toward the right
		if (isSafe(maze, n, col + 1, row))
		{
			// Mark the crossroad as open to come back
			maze[row][col] = 0;
			return PATH_FOUND;
		}
	}	
	
	if (isWithinBoundary(n, col - 1, row))
	{
		// Found a path toward the left
		if (isSafe(maze, n, col - 1, row))
		{
			maze[row][col] = 0;
			return PATH_FOUND;
		}
	}
	
	if (isWithinBoundary(n, col, row - 1))
	{
		// Found a path UP
		if (isSafe(maze, n, col, row - 1))
		{
			maze[row][col] = 0;
			return PATH_FOUND;
		}
	}

	if (isWithinBoundary(n, col, row + 1))
	{
		// Found a path DOWN
		if (isSafe(maze, n, col, row + 1))
		{
			maze[row][col] = 0;
			return PATH_FOUND;
		}
	}

	if (isWithinBoundary(n, col, row + 1))
	{
        if (maze[row + 1][col] == -1)
        {
			pos->y += 1;
			return PATH_NOT_FOUND;
		}
	}

	if (isWithinBoundary(n, col + 1, row))
	{
		if (maze[row][col + 1] == -1)
		{
			pos->x += 1;
			return PATH_NOT_FOUND;
		}
	}	
	
	if (isWithinBoundary(n, col - 1, row))
	{
        if (maze[row][col - 1] == -1)
        {    
			pos->x -= 1;
			return PATH_NOT_FOUND;
		}
	}
	
	if (isWithinBoundary(n, col, row - 1))
	{
        if (maze[row - 1][col] == -1)
        {
			pos->y -= 1;
			return PATH_NOT_FOUND;
		}
	}

	return DEAD_END;
}

int solveMaze(int (*maze)[SIZE], int n, Position *pos)
{
	// Walk to the lower right bottom until it there are no path available
	int col = pos->x, row = pos->y, direction, done;

	output(maze, n, pos);

	if (pos->x == n - 1 && pos->y == n - 1)
		return PATH_FOUND;
	else
	{
		direction = walk(maze, n, pos);

		switch(direction)
		{
			case DOWN:
				maze[row][col] -= 1;
				pos->y += 1;
				return solveMaze(maze, n, pos);
			case RIGHT:
				maze[row][col] -= 1;
				pos->x += 1;
				return solveMaze(maze, n, pos);
			case LEFT:
				maze[row][col] -= 1;
				pos->x -= 1;
				return solveMaze(maze, n, pos);
			case UP:
				maze[row][col] -= 1;
				pos->y -= 1;
				return solveMaze(maze, n, pos);
			case DEAD_END:
				done = PATH_NOT_FOUND;
				while(!done)
				{
					done = backtrack(maze, n, pos);
					output(maze, n, pos);
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

void output(int (*arr)[SIZE], int n, Position *pos)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			
			if (i == pos->y && j == pos->x)
			{
				printf(" x ");
			}
			else if (arr[i][j] == -1)
				printf(" * ");
			else
				printf(" %d ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

// ================ Testing functions ======================
void takeTestInput(FILE *ptr, int (*arr)[SIZE], int n)
{
	int i = 0, j = 0;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			fscanf(ptr, "%d", &arr[i][j]);

}

void test()
{
	char filename[SIZE], answer[SIZE];
	FILE *ptr = NULL;
	int n = 0, arr[SIZE][SIZE], result = 0;
	int count = 0, s = 0;
	Position pos;

	printf("Test cases filename: ");
	scanf("%s", filename);

	ptr = fopen(filename, "r");
	if (ptr == NULL)
	{
		printf("File could not be opened.\n");
		exit(1);
	}

	printf("===== Testing =====\n");
	while(fscanf(ptr, "%d", &n) == 1)
	{
		takeTestInput(ptr, arr, n);
		initPos(&pos);
		result = solveMaze(arr, n, &pos);
		fscanf(ptr, "%s", answer);
		if ((result && !strcmp("Yes", answer)) || (!result && !strcmp("No", answer)))
		{
			s++;
			printf("Test %d passed\n", count + 1);
		}
		else
		{
			printf("Test %d failed\n", count + 1);
			output(arr, n, &pos);
		}
		count++;
	}

	printf("\n===== Summary =====\n");
	if (count - s  == 1)
	{
		printf("%d tests passed\n", s);
		printf("%d test failed\n", count - s);
	}
	else if (count - s > 1)
	{
		printf("%d tests passed\n", s);
		printf("%d tests failed\n", count - s);
	}
	else
	{
		printf("All %d tests passed\n", s);
	}

}

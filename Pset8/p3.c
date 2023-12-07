#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define LEFT 4
#define DOWN 2
#define RIGHT 6
#define UP 8
#define END 5

typedef struct Position
{
	int x;
	int y;
} Position;

void test();
void takeInput(int (*arr)[SIZE], int n, int m);
int displayArray(int (*arr)[SIZE], int n, int m, Position *pos, int direction);
int initPos(Position *pos)
{
	pos->x = 0;
	pos->y = 0;
}

int main()
{
	int arr[SIZE][SIZE], n = 0, m = 0;
	Position pos;

	while(scanf("%d %d", &n, &m) == 2 && n && m)
	{
		takeInput(arr, n, m);
		initPos(&pos);
		displayArray(arr, n, m, &pos, RIGHT);
	}

	return 0;
}

void takeInput(int (*arr)[SIZE], int n, int m)
{
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			scanf("%d", &arr[i][j]);
}

int isSafe(int (*arr)[SIZE], int n, int m, int col, int row)
{
	return (col >= 0 && col < m && row >= 0 && row < n && arr[row][col]);
}

int walk(int (*arr)[SIZE], int n, int m, Position *pos, int d)
{
	int col = pos->x, row = pos->y;

	// If you going down a path in the clockwise direction and it is not possible, do a 90 degree if possible 

	if ((d == RIGHT || d == UP && !isSafe(arr, n, m, col, row - 1)) 
	&& isSafe(arr, n, m, col + 1, row))
		return RIGHT;
	else if ((d == DOWN || d == RIGHT && (!isSafe(arr, n, m, col + 1, row))) 
	&& isSafe(arr, n, m, col, row + 1))
		return DOWN;
	else if ((d == UP || d == LEFT && !isSafe(arr, n, m, col - 1, row)) 
	&& isSafe(arr, n, m, col, row - 1))
		return UP;
	else if ((d == LEFT || d == DOWN && !isSafe(arr, n, m, col, row + 1)) 
	&& isSafe(arr, n, m, col - 1, row))
		return LEFT;
	else
		return END;
}

int displayArray(int (*arr)[SIZE], int n, int m, Position *pos, int direction)
{	
	printf("%d", arr[pos->y][pos->x]);
	arr[pos->y][pos->x] = 0;

	direction = walk(arr, n, m, pos, direction);
	if (direction != END)
		printf(" ");
	switch(direction)
	{
		case LEFT:
			pos->x -= 1;
			return displayArray(arr, n, m, pos, direction);
		case DOWN:
			pos->y += 1;
			return displayArray(arr, n, m, pos, direction);
		case RIGHT:
			pos->x += 1;
			return displayArray(arr, n, m, pos, direction);
		case UP:
			pos->y -= 1;
			return displayArray(arr, n, m, pos, direction);
		default:
		printf("\n");
			return 0;
	}	
	
}
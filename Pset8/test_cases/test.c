#include <stdio.h>

#define SIZE 100
#define UP 8
#define DOWN 2
#define LEFT 4
#define RIGHT 6
#define END 5

void inputMaze(int (*maze)[SIZE], int n);
int solveMaze(int (*maze)[SIZE], int n, int *i, int *j);

int main()
{
    int maze[SIZE][SIZE];
    int n = 0, i, j, answer = 0;

    while (scanf("%d", &n) == 1 && n > 1)
    {
        inputMaze(maze, n);
        i = 0, j = 0;
        
        if (maze[i][j] == 1)
            printf("No\n");
        else
        {
            answer = solveMaze(maze, n, &i, &j);
            if (answer)
		    printf("Yes\n");
	    else
		    printf("No\n");
	}
    }
    
    return 0;
}

void inputMaze(int (*maze)[SIZE], int n)
{
    int i, j;

    for (i = 0; i < n; i++)
        for (j = 0; j< n; j++)
            scanf("%d", &maze[i][j]);
}

int isSafe(int (*maze)[SIZE], int row, int col, int n)
{
    return (row >= 0 && row < n && col >= 0 && col < n && maze[row][col] == 0);
}

int canMove(int (*maze)[SIZE], int row, int col, int n)
{
    // If we can move up, down, left or right
    if (row >= 0 && row < n - 1 && maze[row + 1][col] == 0)
        return DOWN;
    else if (col < n - 1 && maze[row][col + 1] == 0)
        return RIGHT;
    else if (col > 0 && maze[row][col - 1] == 0)
        return LEFT;
    else if (row > 0 && row < n && maze[row - 1][col] == 0)
        return UP;
    else
        return END;

}

void output(int (*maze)[SIZE], int n, int *row, int *col)
{
    int i, j;

    printf("Current value : %d\n", maze[*row][*col]);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == *row && j == *col)
                printf("  @  ");
            else if (maze[i][j] == -1)
                printf("  -  ");
            else if (maze[i][j] == -2)
                printf("  *  ");
            else
                printf("  %d  ", maze[i][j]);
        }
        printf("\n");
    }
}

int backtrack(int (*maze)[SIZE], int n, int *i, int *j)
{
    int temp[2];

    // Find another path
    if (*i > 0 && maze[*i - 1][*j] == 0 || *i < n - 1 && maze[*i + 1][*j] == 0 ||
    *j > 0 && maze[*i][*j - 1] == 0 || *j < n - 1 && maze[*i][*j + 1] == 0)
    {
        maze[*i][*j] -= 1;
        if (*i >  0 && maze[*i - 1][*j] == 0)
            *i -= 1;
        else if (*i < n - 1 && maze[*i + 1][*j] == 0)
            *i += 1;
        else if (*j > 0 && maze[*i][*j - 1] == 0)
            *j -= 1;
        else if (*j < n - 1 && maze[*i][*j + 1] == 0)
            *j += 1;

        return 1;
    }

    if (*i > 0 && maze[*i - 1][*j] < 0 || *i < n - 1 && maze[*i + 1][*j] < 0 ||
    *j > 0 && maze[*i][*j - 1] < 0 || *j < n - 1 && maze[*i][*j + 1] < 0)
    {
        if (maze[*i][*j] <= 0)
            maze[*i][*j] -= 1;

        if (*i > 0 && maze[*i - 1][*j] == -1)
            *i -= 1;
        else if (*i < n - 1 && maze[*i + 1][*j] == -1)
            *i += 1;
        else if (*j > 0 && maze[*i][*j - 1] == -1)
            *j -= 1;
        else if (*j < n - 1 && maze[*i][*j + 1] == -1)
            *j += 1;
        else
        {
            printf("\nValue : %d\n", maze[*i][*j]);
            if (maze[*i][*j] == -2)
            {
                temp[0] = *i;
                temp[1] = *j;
                if (*i < n -1 && (maze[*i + 1][*j] == -1 || maze[*i + 1][*j] == 0))
                    *i += 1;
                else if (*j < n -1 && (maze[*i][*j + 1] == -1 || maze[*i][*j + 1] == 0))
                    *j += 1;
                else if (*j > 0 && (maze[*i][*j - 1] == -1 || maze[*i][*j - 1] == 0))
                    *j -= 1;
                else if (*i > 0 && (maze[*i - 1][*j] == -1 || maze[*i - 1][*j] == 0))
                    *i -= 1;
                
                maze[temp[0]][temp[1]] = 1;

                return 0;
            }

            return -2;
        }
        return 0;
    }

    return -2;
}

int solveMaze(int (*maze)[SIZE], int n, int *i, int *j)
{
    int d = RIGHT, b = 0;

    // output(maze, n, i, j);

    while(isSafe(maze, *i, *j, n))
    {
        if (*i == n - 1 && *j == n - 1)
            break;

        d = canMove(maze, *i, *j, n);
        maze[*i][*j] -= 1;

        output(maze, n, i ,j);

        if (d == UP)
            *i -= 1;
        else if(d == DOWN)
            *i += 1;
        else if (d == LEFT)
            *j -= 1;
        else if (d == RIGHT)
            *j += 1;
        else
        {
            b = 0;
            while(b == 0)
            {
                if (*i == n - 1 && *j == n - 1)
                    break;

                b = backtrack(maze, n, i, j);
                output(maze, n, i, j);
            }

            if (*i == n - 1 && *j == n - 1)
                break;

            if (b == -2)
                break;
        } 
    }

    output(maze, n, i, j);
    return (*i == n - 1 && *j == n - 1 && maze[*i][*j] != 1);
}

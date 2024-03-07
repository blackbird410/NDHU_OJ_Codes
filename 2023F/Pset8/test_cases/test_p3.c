#include "p3.c"

typedef struct Answer 
{
	int answer[SIZE];
	int index;
} Answer;

int main()
{
    test();
}

void initAnswer(Answer *a)
{
	a->index = 0;
	while (a->index < SIZE)
	{
		a->answer[a->index] = 0;
		a->index += 1;
	}
	a->index = 0;

}

void takeTestInput(int (*arr)[SIZE], int n, int m, FILE *ptr)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < m; j++)
			fscanf(ptr, "%d", &arr[i][j]);
}

int testDisplayArray(int (*arr)[SIZE], int n, int m, Position *pos, Answer *a)
{
    if (arr[pos->y][pos->x] != a->answer[a->index])
        return -1;
    arr[pos->y][pos->x] = 0;

    int direction = walk(arr, n, m, pos, direction);
	if (direction != END)
		a->index += 1;
    
    switch(direction)
    {
            case LEFT:
                    pos->x += 1;
                    return testDisplayArray(arr, n, m, pos, a);
            case DOWN:
                    pos->y += 1;
                    return testDisplayArray(arr, n, m, pos, a);
            case RIGHT:
                    pos->x -= 1;
                    return testDisplayArray(arr, n, m, pos, a);
            case UP:
                    pos->y -= 1;
                    return testDisplayArray(arr, n, m, pos, a);
            default:
                    return 0;
    }

}

void takeAnswer(Answer *a, int n, FILE *ptr)
{
	int i;
	for (i = 0; i < n; i++)
		fscanf(ptr, "%d", &a->answer[i]);
}


void test()
{
	FILE *ptr = NULL;
	
	ptr = fopen("test_cases_p3.txt", "r");
	if (ptr == NULL)
	{
		printf("File could not be opened.\n");
		exit(1);
	}

	int n = 0, m = 0, arr[SIZE][SIZE];
	Position pos;
	int passed = 0, tests = 0;
	Answer a;

	while(fscanf(ptr, "%d %d", &n, &m) == 2 && n && m)
	{
		takeTestInput(arr, n, m, ptr);
		initPos(&pos);
        initAnswer(&a);
		takeAnswer(&a, n*m, ptr);
        
		if (!testDisplayArray(arr, n, m, &pos, &a))
			passed++;
		else
		{
			printf("Test %d failed\n", tests + 1);
		}
		tests++;
	}

	if (passed == tests)
		printf("All %d tests passed.\n", tests);
	else
		printf("%d test(s) passed | %d test(s) failed\n", passed, tests-passed);

}
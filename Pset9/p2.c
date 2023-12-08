
#define ROW1 0
#define COL1 4
#define ROW2 4
#define COL2 3
#define ROWS 9
#define COLS 7

int main() 
{
    int *p;
    init(&p);    
  	int value1 = *(p + ROW1 * COLS + COL1);
    int value2 = *(p + ROW2 * COLS + COL2);

    printf("%d, %d", value1, value2);
    
    return 0;
}

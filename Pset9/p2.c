#define ROW1 0
#define COL1 4
#define ROW2 4
#define COL2 3

int main() 
{
    int *p = NULL;
    init(&p);
    
    int v1 = *((int *)(p + ((ROW1 + COL1) * sizeof(int))));
    int v2 = *((int *)(p + ((ROW2 + COL2) * sizeof(int))));
    printf("%d, %d", v1, v2);

    free(p);
    return 0;
}

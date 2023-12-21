#include <stdio.h>
#include <string.h>

#define SIZE 100

int f(int x);
int g(int x, int y);
int eval(char *s);

// F(G(F(2), 1))
// F(G(7, 1))

int main()
{
    char s[SIZE];
    fgets(s, SIZE, stdin);
    
    eval(s);
    printf("%s\n", s);
    return 0;
}

int eval(char *s)
{
    if (s[0] >= '0' && s[0] <= '9')
        return 0;
    
    printf("%s\n", s);

    int i = 0, j = 0, pos = 0, x = 0, y = 0, k = 0;
    char result[SIZE];

    while(s[i] != '\n' && s[i] != '\0')
    {
        pos = (s[i] == 'F' || s[i] == 'G') ? i : pos;
        i++;
    }

    for (i = 0; i < pos; i++)
        result[i] = s[i];

    // Evaluate inner expression and replace in string
    if (s[pos] == 'F')
    {
        // Get the x value
        while (s[pos + k + 2] != ')')
        {
            x = (x * 10) + (s[pos + k + 2] - '0');
            k++;
        }
        
        j = f(x);
        // Writing the result
        while(j)
        {
            result[i] = j % 10 + '0';
            j /= 10;
            i++;
        }

        // Writing rest of operation if there is any
        pos += k + 3;
        while (s[i] != '\n' && s[i] != '\0')
        {
            result[i] = s[pos];
            i++;
            pos++;
        }

        strcpy(s, result);
        eval(s);
    }
    else if (s[pos] == 'G')
    {
        // F(G(7, 1))
        // Get the x value
        k += 2;
        while (s[pos + k] != ',')
        {
            x = (x * 10) + (s[pos + k] - '0');
            k++;
        }

        // Get the y value
        while (s[pos + k] != ')')
        {
            y = (y * 10) + (s[pos + k] - '0');
            k++;
        }

        j = g(x, y);
        // Writing the result
        while(j)
        {
            result[i] = j % 10 + '0';
            j /= 10;
            i++;
        }

        // Writing rest of operation if there is any
        pos += k + 3;
        while (s[i] != '\n' && s[i] != '\0')
        {
            result[i] = s[pos];
            i++;
            pos++;
        }

        strcpy(s, result);
        eval(s);
    }
    else
    {
        printf("Error\n");
    }
}

int f(int x)
{
    return 3 * x + 1;
}

int g(int x, int y)
{
    return x * y - 3;
}
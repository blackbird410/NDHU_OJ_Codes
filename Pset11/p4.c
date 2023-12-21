#include <stdio.h>
#include <string.h>

#define SIZE 100

int f(int x);
int g(int x, int y);
int eval(char *s);

// F(G(F(2), 1))
// F(G(7, F(1)))

int main()
{
    char s[SIZE];
    gets(s);
    
    eval(s);
    printf("%s\n", s);
    return 0;
}

char *getNum(int j, char *n)
{
    int l = 0, i = 0;

    while(j)
    {
        n[l] = j % 10 + '0';
        j /= 10;
        l++;
    }
    n[l] = '\0';

    if (l == 1)
        return n;

    while(i < l / 2)
    {
        n[i] += n[l - i - 1];
        n[l - i - 1] = n[i] - n[l - i - 1];
        n[i] -= n[l - i - 1]; 

        i++;
    }

    return n;
}

int eval(char *s)
{
    if (s[0] >= '0' && s[0] <= '9')
        return 0;
    
    // printf("%s\n", s);

    int i = 0, j = 0, pos = 0, x = 0, y = 0, k = 0, l = 0;
    char result[SIZE], n[SIZE];

    while(s[i] != '\0')
    {
        pos = (s[i] == 'F' || s[i] == 'G') ? i : pos;
        i++;
    }

    for (i = 0; i < pos; i++)
        result[i] = s[i];

    // Evaluate inner expression and replace in string
    if (s[pos] == 'F')
    {
        // F(G(F(2), 1))
        // Get the x value
        k = 2;
        while (s[pos + k] != ')')
        {
            x = (x * 10) + (s[pos + k] - '0');
            k++;
        }
        
        j = f(x);
        // Writing the result
        getNum(j, n);
        while(n[l] != '\0')
        {
            result[i + l] = n[l];
            l++;
        }
        i += l;

        // Writing rest of operation if there is any
        pos += k + 1;
        while (s[pos] != '\0')
        {
            result[i] = s[pos];
            i++;
            pos++;
        }
        result[i] = '\0';

        strcpy(s, result);
        eval(s);
    }
    else if (s[pos] == 'G')
    {
        // F(G(7, 1))
        // Get the x value
        k = 2;
        while (s[pos + k] != ',')
        {
            x = (x * 10) + (s[pos + k] - '0');
            k++;
        }

        // Get the y value
        k += 2;
        while (s[pos + k] != ')')
        {
            y = (y * 10) + (s[pos + k] - '0');
            k++;
        }

        j = g(x, y);
        // Writing the result
        getNum(j, n);
        while(n[l] != '\0')
        {
            result[i + l] = n[l];
            l++;
        }
        i += l;

        // Writing rest of operation if there is any
        pos += k + 1;
        while (s[pos] != '\n' && s[pos] != '\0')
        {
            result[i] = s[pos];
            i++;
            pos++;
        }
        result[i] = '\0';

        strcpy(s, result);
        eval(s);
    }

    return 1;
}

int f(int x)
{
    return 3 * x + 1;
}

int g(int x, int y)
{
    return x * y - 3;
}
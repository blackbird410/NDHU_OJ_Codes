#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SPACE 32
#define MAX_LIMIT 1000
#define PI 3.141593
#define NUMBERS_LOWER_BOUND 46
#define NUMBERS_UPPER_BOUND 58

void get_string(char *word);
void split(char* str, int *list);
double get_max_volume(int n, int f, int* radii);
double max(int *arr, int size);

int main(int argc, char* argv)
{
    // Get the inputs
    char str[20];
    get_string(str);
    int test_cases = atoi(str);

    char n_f[MAX_LIMIT];
    int l[MAX_LIMIT];
    char radii[MAX_LIMIT];
    int radii_l[MAX_LIMIT];
    char result[MAX_LIMIT];
    char int_value[MAX_LIMIT];

    int n = 0, f = 0;
    double v = 0;
   
    for (int i = 0; i < test_cases; i++)
    {
      get_string(n_f);
        
      // Split the string to get the number of pie and the number of friends
      split(n_f, l);

      n = l[0];
      f = l[1];
         
      // Get the radii
      get_string(radii);
      split(radii, radii_l);

      v = get_max_volume(n, f, radii_l);

      // Format the result
      itoa((int) v, int_value, 10);

      int length = strlen(int_value);

      gcvt(v, length + 4, result);

      printf("%s\n", result);

    }
}

void get_string(char *word)
{
    char c;
    int i = 0;
    do
    {
        c = getchar();
        if (c != 10)
        {
            word[i] = c;
            i++;
        }
    } while (c != 10);
    word[i]= '\0';
}

void split(char* str, int *list)
{
    int i = 0, k = 0, l = 0;
    int length = strlen(str);

    char number[MAX_LIMIT];

    for (i = 0; i < length; i++)
    {
        // Check if it is a number
        if(str[i] > NUMBERS_LOWER_BOUND && str[i] < NUMBERS_UPPER_BOUND)
        {
            number[l] = str[i];
            l++;
        }
        else
        {
            number[l] = '\0';
            // Convert the string to an integer and add it to the list
            list[k] = atoi(number);

            l = 0;
            k++;
        }
    }
    number[l] = '\0';
    list[k] = atoi(number);
}


double get_max_volume(int n, int f, int* radii)
{
    //Returns the maximum volume of pie each person can have based on the number of pie(n), the number of friends(n) and the different radius in the radii list.

    if (n == 1)
    {
        return (PI * radii[0] * radii[0]) / (f + 1);  
    }

    // Binary search algorithm
    double min_v  = 0;
    double max_elt = max(radii, n);
    double max_v = PI * max_elt * max_elt;

    // Mid range value of the interval from 0 to the volume of the largest pie
    double v = (min_v + max_v) / 2;

    // Find the largest volume a pie can be divided into for everyone to have one piece of one pie
    int counter = 0;
    double pieces = 0;
    double pie_v = 0;
    double prev_v = 0;

    while (counter == 0)
    {
        pieces = 0;
        for (int j = 0; j < n; j++)
        {
            pie_v = PI * pow(radii[j], 2);
            pieces += floor(pie_v / v);
        }

        if (pieces > f + 1)
        {
            // Too small slices
            min_v = (min_v + max_v) / 2;
        }
        else if (pieces < f + 1)
        {
            // Too big slices
            max_v = (min_v + max_v) / 2;
        }

        // Record the previous value to know when we reach the limit of the algorithm (cannot divide any further)
        prev_v = v;
        v = (min_v + max_v) / 2;

        if (prev_v == v)
        {  
            return v;
        }
    }
}

double max(int *arr, int size)
{
    // Get the maximun positive element of an array
    
    int i = 0;
    double m  = 0;
    for (i = 0; i < size; i++)
    {
        if (arr[i] > m)
        {
            m = arr[i];
        }
    }

    return m;
}


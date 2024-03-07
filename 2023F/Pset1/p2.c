#include <stdio.h>

int main()
{
  // Initialize the variables
  int myInt = 0;
  double myDouble = 0;
  char myChar;
  
  // Read the inputs
  scanf("%d %lf %c", &myInt, &myDouble, &myChar);
  
  // Print the inputs
  printf("%d\n%lf\n%c", myInt, myDouble, myChar);
  
  return 0;
}
#include <stdio.h>


int main()
{
  char userChar;
  
  // Read the character
  scanf("%c", &userChar);
  
  // Print the character
  printf("%d\n%c", userChar, userChar);

  return 0;
}
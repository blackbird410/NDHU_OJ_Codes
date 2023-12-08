#include <stdio.h>

int main() 
{
  init();
  void *p = &block;
  printf("%d, %c, %f", *((int *)p), *((char *)(p + sizeof(int))), *((float*)(p + sizeof(int) + sizeof(char))));
  
  return 0;
}

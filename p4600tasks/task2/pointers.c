#include <stdio.h>
#include <stdlib.h>

int main()
{
  int array [] = {12,14,16,18};

  //printf("%d",array[2]);

  int* cursor = array;
  int i;
  for(i = 0; i<4; i++)
    {
      printf("\n%d",*cursor);
      cursor++;
    }
}
